#include "SoftwareReview.h"

SoftwareReview::SoftwareReview(const QString& name, const QDate& date, bool recommended)
    : mName(name), mDate(date), mRecommended(recommended) {}

QString SoftwareReview::getName() const {
    return mName;
}

QDate SoftwareReview::getDate() const {
    return mDate;
}

bool SoftwareReview::isRecommended() const {
    return mRecommended;
}

QVariantMap SoftwareReview::toVariantMap() const {
    QVariantMap map;
    map.insert("Name", mName);
    map.insert("Date", mDate);
    map.insert("Recommended", mRecommended);
    return map;
}
