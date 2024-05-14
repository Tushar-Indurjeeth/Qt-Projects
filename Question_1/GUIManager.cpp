#include "GUIManager.h"
#include "ReviewManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QLineEdit>
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>


GUIManager::GUIManager(QWidget *parent)
    : QWidget(parent), mReviewManager(new ReviewManager)
{
    // Create input fields and buttons
    QLabel *nameLabel = new QLabel("Name:");
    mNameEdit = new QLineEdit;
    QLabel *dateLabel = new QLabel("Date:");
    mDateEdit = new QDateEdit(QDate::currentDate());
    QLabel *recommendedLabel = new QLabel("Recommended:");
    mRecommendedCheckBox = new QCheckBox;
    mAddButton = new QPushButton("Add Review");
    mPrintButton = new QPushButton("Print Reviews");

    // Connect buttons to slots
    connect(mAddButton, &QPushButton::clicked, this, &GUIManager::addReview);
    connect(mPrintButton, &QPushButton::clicked, this, &GUIManager::printReviews);

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(mNameEdit);
    QHBoxLayout *dateLayout = new QHBoxLayout;
    dateLayout->addWidget(dateLabel);
    dateLayout->addWidget(mDateEdit);
    QHBoxLayout *recommendedLayout = new QHBoxLayout;
    recommendedLayout->addWidget(recommendedLabel);
    recommendedLayout->addWidget(mRecommendedCheckBox);
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(dateLayout);
    mainLayout->addLayout(recommendedLayout);
    mainLayout->addWidget(mAddButton);
    mainLayout->addWidget(mPrintButton);
}

void GUIManager::addReview() {
    QString name = mNameEdit->text();
    QDate date = mDateEdit->date();
    bool recommended = mRecommendedCheckBox->isChecked();

    // Validate input
    if (name.isEmpty()) {
        qDebug() << "Name cannot be empty!";
        return;
    }

    // Add review to manager
    mReviewManager->addReview(SoftwareReview(name, date, recommended));

    // Clear input fields
    mNameEdit->clear();
    mDateEdit->setDate(QDate::currentDate());
    mRecommendedCheckBox->setChecked(false);

    qDebug() << "Review added successfully!";
}

void GUIManager::printReviews() {
    mReviewManager->printReviews();
}
