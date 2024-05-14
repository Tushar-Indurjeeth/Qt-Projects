#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QWidget>

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

private:
    QLineEdit *mNameEdit;
    QDateEdit *mDateEdit;
    QCheckBox *mRecommendedCheckBox;
    QPushButton *mAddButton;
    QPushButton *mPrintButton;
    ReviewManager *mReviewManager;
};

#endif // GUIMANAGER_H
