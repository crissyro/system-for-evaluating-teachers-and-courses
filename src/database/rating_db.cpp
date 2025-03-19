#include "../../include/database/rating_db.hpp"

namespace database {

RatingDB::RatingDB(const Database& database) : db(database.getHandle()) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS course_ratings (
            student_id INTEGER NOT NULL,
            course_id INTEGER NOT NULL,
            rating INTEGER CHECK(rating BETWEEN 1 AND 5),
            FOREIGN KEY(student_id) REFERENCES students(id),
            FOREIGN KEY(course_id) REFERENCES courses(id)
        );)";

    Database::Statement stmt(db, sql);
    sqlite3_step(stmt);

    sql = R"(
        CREATE TABLE IF NOT EXISTS teacher_ratings (
            student_id INTEGER NOT NULL,
            teacher_id INTEGER NOT NULL,
            rating INTEGER CHECK(rating BETWEEN 1 AND 5),
            FOREIGN KEY(student_id) REFERENCES students(id),
            FOREIGN KEY(teacher_id) REFERENCES teachers(id)
        );)";
        
    Database::Statement stmt2(db, sql);
    sqlite3_step(stmt2);
}

bool RatingDB::addTeacherRating(int studentId, int teacherId, int rating) {
    const char* sql = "INSERT INTO teacher_ratings VALUES (?, ?, ?);";

    Database::Statement stmt(db, sql);
    stmt.bind(1, studentId);
    stmt.bind(2, teacherId);
    stmt.bind(3, rating);

    return sqlite3_step(stmt) == SQLITE_DONE;
}

RatingDB::Statistics RatingDB::getStatistics() {
    Statistics stats{};
    
    const char* sql = R"(
        SELECT 
            AVG(SELECT rating FROM course_ratings),
            AVG(SELECT rating FROM teacher_ratings)
    )";
    
    Database::Statement stmt(db, sql);

    if(sqlite3_step(stmt) == SQLITE_ROW) {
        stats.avgCourseRating = sqlite3_column_double(stmt, 0);
        stats.avgTeacherRating = sqlite3_column_double(stmt, 1);
    }

    return stats;
}

std::vector<rating::Rating> RatingDB::getAllRatings() {
    std::vector<rating::Rating> ratings;

    const char* sql = R"(
        SELECT 'course' as type, student_id, course_id, rating FROM course_ratings
        UNION ALL
        SELECT 'teacher', student_id, teacher_id, rating FROM teacher_ratings
    )";
    
    Database::Statement stmt(db, sql);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        ratings.emplace_back(
            sqlite3_column_int(stmt, 1),
            sqlite3_column_int(stmt, 2),
            sqlite3_column_int(stmt, 3),

            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))) == "course"
        );
    }

    return ratings;
}

} // namespace database