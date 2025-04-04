#include "../../include/database/course_db.hpp"

namespace database {

CourseDB::CourseDB(const Database& database) : db(database.getHandle()) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS courses (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            institute TEXT NOT NULL
        );)";

    Database::Statement stmt(db, sql);
    sqlite3_step(stmt);
}

int CourseDB::addCourse(const course::Course& course) {
    const char* sql = "INSERT INTO courses (name, institute) VALUES (?, ?);";

    Database::Statement stmt(db, sql);
    stmt.bind(1, course.getName());
    stmt.bind(2, course.getInstitute());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Failed to add course");
    }

    return sqlite3_last_insert_rowid(db);
}

course::Course CourseDB::getCourse(int id) {
    const char* sql = "SELECT * FROM courses WHERE id = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        return course::Course(sqlite3_column_int(stmt, 0), reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                              reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    }

    throw std::runtime_error("Course not found");
}

bool CourseDB::exists(int courseId) {
    const char* sql = "SELECT 1 FROM courses WHERE id = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, courseId);

    return sqlite3_step(stmt) == SQLITE_ROW;
}

std::vector<course::Course> CourseDB::getAllCourses() {
    std::vector<course::Course> courses;
    const char* sql = "SELECT * FROM courses;";

    Database::Statement stmt(db, sql);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        courses.emplace_back(sqlite3_column_int(stmt, 0), reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                             reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    }

    return courses;
}

}  // namespace database