#include "../../include/database/rating_db.hpp"

namespace database
{

RatingDB::RatingDB(const Database& database) : db(database.getHandle())
{
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS course_ratings (
            student_id INTEGER NOT NULL,
            course_id INTEGER NOT NULL,
            rating INTEGER CHECK(rating BETWEEN 1 AND 5),
            UNIQUE(student_id, course_id),
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
            UNIQUE(student_id, teacher_id),
            FOREIGN KEY(student_id) REFERENCES students(id),
            FOREIGN KEY(teacher_id) REFERENCES teachers(id)
        );)";

    Database::Statement stmt2(db, sql);
    sqlite3_step(stmt2);
}

bool RatingDB::addTeacherRating(int studentId, int teacherId, int rating)
{
    const char* sql = "INSERT INTO teacher_ratings VALUES (?, ?, ?);";

    Database::Statement stmt(db, sql);
    stmt.bind(1, studentId);
    stmt.bind(2, teacherId);
    stmt.bind(3, rating);

    return sqlite3_step(stmt) == SQLITE_DONE;
}

bool RatingDB::hasExistingRating(int studentId, int entityId, bool isCourse)
{
    const char* sql;
    if (isCourse)
    {
        sql = "SELECT 1 FROM course_ratings WHERE student_id = ? AND course_id = ?;";
    }
    else
    {
        sql =
            "SELECT 1 FROM teacher_ratings WHERE student_id = ? AND teacher_id = "
            "?;";
    }

    Database::Statement stmt(db, sql);
    stmt.bind(1, studentId);
    stmt.bind(2, entityId);

    return sqlite3_step(stmt) == SQLITE_ROW;
}

RatingDB::Statistics RatingDB::getStatistics()
{
    Statistics stats;

    const char* course_sql = R"(
        SELECT course_id, AVG(rating) 
        FROM course_ratings 
        GROUP BY course_id;)";

    Database::Statement course_stmt(db, course_sql);
    while (sqlite3_step(course_stmt) == SQLITE_ROW)
    {
        stats.courseStats.emplace_back(sqlite3_column_int(course_stmt, 0), sqlite3_column_double(course_stmt, 1));
    }

    const char* teacher_sql = R"(
        SELECT teacher_id, AVG(rating) 
        FROM teacher_ratings 
        GROUP BY teacher_id;)";

    Database::Statement teacher_stmt(db, teacher_sql);
    while (sqlite3_step(teacher_stmt) == SQLITE_ROW)
    {
        stats.teacherStats.emplace_back(sqlite3_column_int(teacher_stmt, 0), sqlite3_column_double(teacher_stmt, 1));
    }

    return stats;
}

std::vector<rating::Rating> RatingDB::getAllRatings()
{
    std::vector<rating::Rating> ratings;

    const char* sql = R"(
        SELECT 'course' as type, student_id, course_id, rating FROM course_ratings
        UNION ALL
        SELECT 'teacher', student_id, teacher_id, rating FROM teacher_ratings
    )";

    Database::Statement stmt(db, sql);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        ratings.emplace_back(sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2), sqlite3_column_int(stmt, 3),

                             std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))) == "course");
    }

    return ratings;
}

std::vector<std::pair<int, int>> RatingDB::getCourseRatings(int studentId)
{
    std::vector<std::pair<int, int>> ratings;
    const char* sql = "SELECT course_id, rating FROM course_ratings WHERE student_id = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, studentId);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        ratings.emplace_back(sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1));
    }

    return ratings;
}

std::vector<std::pair<int, int>> RatingDB::getTeacherRatings(int studentId)
{
    std::vector<std::pair<int, int>> ratings;
    const char* sql = "SELECT teacher_id, rating FROM teacher_ratings WHERE student_id = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, studentId);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        ratings.emplace_back(sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1));
    }

    return ratings;
}

std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> RatingDB::getStudentRatings(int studentId)
{
    return {getCourseRatings(studentId), getTeacherRatings(studentId)};
}

bool RatingDB::addCourseRating(int studentId, int courseId, int rating)
{
    const char* sql = R"(
        INSERT OR REPLACE INTO course_ratings 
        (student_id, course_id, rating) 
        VALUES (?, ?, ?);)";

    Database::Statement stmt(db, sql);
    stmt.bind(1, studentId);
    stmt.bind(2, courseId);
    stmt.bind(3, rating);

    return sqlite3_step(stmt) == SQLITE_DONE;
}

}  // namespace database