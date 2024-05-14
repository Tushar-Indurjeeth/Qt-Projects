#include "ReviewManager.h"
#include <iostream>

void ReviewManager::addReview(const SoftwareReview& review) {
    mReviews.push_back(review);
}

void ReviewManager::printReviews() const {
    for (const auto& review : mReviews) {
        std::cout << "Name: " << review.getName().toStdString() << std::endl;
        std::cout << "Date: " << review.getDate().toString("yyyy-MM-dd").toStdString() << std::endl;
        std::cout << "Recommended: " << (review.isRecommended() ? "Yes" : "No") << std::endl << std::endl;
    }
}
