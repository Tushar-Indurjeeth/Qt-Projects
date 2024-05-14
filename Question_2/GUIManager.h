#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QWidget>
#include <QVariantMap>

class QLineEdit;
class QCheckBox;
class QPushButton;
class QDateEdit;
class ReviewManager;

class GUIManager : public QWidget {
    Q_OBJECT
public:
    explicit GUIManager(QWidget *parent = nullptr);

private slots:
    void addReview();
    void printReviews();
    void displayReviewDetails();

private:
    void displayReview(const QVariantMap& review);

    QLineEdit *mNameEdit;
    QDateEdit *mDateEdit;
    QCheckBox *mRecommendedCheckBox;
    QPushButton *mAddButton;
    QPushButton *mPrintButton;
    QPushButton *mDisplayButton;
    ReviewManager *mReviewManager;
};

#endif // GUIMANAGER_H
