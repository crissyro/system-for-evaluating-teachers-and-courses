#pragma once

#include <vector>
#include "database.hpp"
#include "../classes/rating.hpp"

namespace database {

class RatingDB {
private:
    sqlite3* db;
    
public:
    struct Statistics {
        double avgCourseRating;
        double avgTeacherRating;
    };

    explicit RatingDB(const Database& database);

    ~RatingDB() = default;
    
    bool addCourseRating(int studentId, int courseId, int rating);

    bool addTeacherRating(int studentId, int teacherId, int rating);
    
    std::vector<rating::Rating> getAllRatings();

    Statistics getStatistics();

}; // class Rating

} // namespace database