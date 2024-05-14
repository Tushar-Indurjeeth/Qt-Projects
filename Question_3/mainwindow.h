#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

class QTableView;
class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addRow();
    void deleteRow();
    void updateRowColor(const QModelIndex &index);
    void updateReplacementValue();

private:
    QTableView *tableView;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QLineEdit *composerLineEdit;
    QLineEdit *albumLineEdit;
    QLineEdit *replacementValueLineEdit;
    QLineEdit *ratingLineEdit;
    QStandardItemModel *model;

    void setupGUI();
    void setupModel();
};

#endif // MAINWINDOW_H
