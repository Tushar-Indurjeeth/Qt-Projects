#ifndef SOFTWAREREVIEW_H
#define SOFTWAREREVIEW_H

#include <QString>
#include <QDate>
#include <QVariantMap>

class SoftwareReview {
public:
    SoftwareReview(const QString& name, const QDate& date, bool recommended);

    QString getName() const;
    QDate getDate() const;
    bool isRecommended() const;
    QVariantMap toVariantMap() const; // Function for reflective programming

private:
    QString mName;
    QDate mDate;
    bool mRecommended;
};

#endif // SOFTWAREREVIEW_H
