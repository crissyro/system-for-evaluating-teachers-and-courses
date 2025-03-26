#pragma once

#include <vector>
#include <utility>
#include "database.hpp"
#include "../classes/rating.hpp"

namespace database {

class RatingDB {
private:
    sqlite3* db;
    
public:
    struct Statistics {
        std::vector<std::pair<int, double>> courseStats;  // <course_id, avg_rating>
        std::vector<std::pair<int, double>> teacherStats; // <teacher_id, avg_rating>
    };

    explicit RatingDB(const Database& database);

    ~RatingDB() = default;
    
    bool addCourseRating(int studentId, int courseId, int rating);

    bool addTeacherRating(int studentId, int teacherId, int rating);
    
    std::vector<rating::Rating> getAllRatings();

    Statistics getStatistics();

    bool hasExistingRating(int studentId, int entityId, bool isCourse);

    std::vector<std::pair<int, int>> getCourseRatings(int studentId);

    std::vector<std::pair<int, int>> getTeacherRatings(int studentId);

    std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> getStudentRatings(int studentId);

}; // class Rating

} // namespace database