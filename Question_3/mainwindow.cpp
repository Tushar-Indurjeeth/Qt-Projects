#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QLineEdit>
#include <QItemDelegate>
#include <QPainter>
#include <QApplication>

class RatingDelegate : public QItemDelegate
{
public:
    RatingDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = index.data().toInt();
        progressBarOption.text = QString::number(progressBarOption.progress) + " %";
        progressBarOption.textVisible = true;

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupGUI();
    setupModel();

    connect(replacementValueLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateReplacementValue);
    connect(model, &QStandardItemModel::dataChanged, this, &MainWindow::updateRowColor);
}

MainWindow::~MainWindow()
{
    delete model;
}

void MainWindow::setupGUI()
{
    tableView = new QTableView(this);
    model = new QStandardItemModel(0, 4, this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setItemDelegateForColumn(3, new RatingDelegate(this));

    composerLineEdit = new QLineEdit(this);
    composerLineEdit->setPlaceholderText("Composer");

    albumLineEdit = new QLineEdit(this);
    albumLineEdit->setPlaceholderText("Album Name");

    replacementValueLineEdit = new QLineEdit(this);
    replacementValueLineEdit->setPlaceholderText("Replacement Value");

    // Set up validator for replacementValueLineEdit
    QDoubleValidator *validator = new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    replacementValueLineEdit->setValidator(validator);

    // Set up validator for ratingLineEdit
    QIntValidator *ratingValidator = new QIntValidator(0, 100, this);
    ratingLineEdit = new QLineEdit(this);
    ratingLineEdit->setPlaceholderText("Rating (0-100)");
    ratingLineEdit->setValidator(ratingValidator);

    addButton = new QPushButton("Add Row", this);
    deleteButton = new QPushButton("Delete Row", this);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRow);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRow);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableView);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(composerLineEdit);
    inputLayout->addWidget(albumLineEdit);
    inputLayout->addWidget(replacementValueLineEdit);
    inputLayout->addWidget(ratingLineEdit);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(deleteButton);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupModel()
{
    QStringList headers = {"Composer", "Album Name", "Replacement Value", "Rating"};
    model->setHorizontalHeaderLabels(headers);

    // Enable sorting for the table view
    tableView->setSortingEnabled(true);
}

void MainWindow::addRow()
{
    QString composer = composerLineEdit->text();
    QString albumName = albumLineEdit->text();
    QString replacementValueText = replacementValueLineEdit->text();
    QString ratingText = ratingLineEdit->text();

    if (composer.isEmpty() || albumName.isEmpty() || replacementValueText.isEmpty() || ratingText.isEmpty()) {
        QMessageBox::critical(this, "Error", "All fields must be filled.");
        return;
    }

    // Convert replacementValueText to double with two decimal points
    double replacementValue = QString(replacementValueText).toDouble();
    replacementValue = qRound(replacementValue * 100) / 100.0;

    // Convert ratingText to integer
    int rating = QString(ratingText).toInt();

    if (rating > 100) {
        QMessageBox::critical(this, "Error", "Rating must be between 0 and 100.");
        return;
    }

    // Create items for each column
    QList<QStandardItem*> rowItems;
    rowItems << new QStandardItem(composer);
    rowItems << new QStandardItem(albumName);
    rowItems << new QStandardItem(QString::number(replacementValue, 'f', 2));
    rowItems << new QStandardItem(QString::number(rating));

    // Append the row to the model
    model->appendRow(rowItems);

    // Clear input fields
    composerLineEdit->clear();
    albumLineEdit->clear();
    replacementValueLineEdit->clear();
    ratingLineEdit->clear();

    // Check if the replacement value is greater than or equal to R200
    QModelIndex lastIndex = model->index(model->rowCount() - 1, 2);
    if (replacementValue >= 200.0) {
        model->setData(lastIndex, QBrush(Qt::red), Qt::BackgroundRole);
    }
}


void MainWindow::deleteRow()
{
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
    }
}

void MainWindow::updateReplacementValue()
{
    QString value = replacementValueLineEdit->text();
    QString formattedValue = QString::number(value.toDouble(), 'f', 2);
    replacementValueLineEdit->setText(formattedValue);
}

void MainWindow::updateRowColor(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    double replacementValue = index.sibling(index.row(), 2).data().toDouble();
    if (replacementValue >= 200.0) {
        QBrush brush(Qt::red);
        model->itemFromIndex(index)->setBackground(brush);
    } else {
        model->itemFromIndex(index)->setBackground(QBrush());
    }
}
