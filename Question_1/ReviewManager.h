#ifndef REVIEWMANAGER_H
#define REVIEWMANAGER_H

#include <vector>
#include "SoftwareReview.h"

class ReviewManager {
public:
    void addReview(const SoftwareReview& review);
    void printReviews() const;

private:
    std::vector<SoftwareReview> mReviews;
};

#endif // REVIEWMANAGER_H
