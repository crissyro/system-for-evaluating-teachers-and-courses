#pragma once

#include "database.hpp"
#include "../classes/course.hpp"

namespace database {

class CourseDB {
    sqlite3* db;
    
public:
    explicit CourseDB(const Database& database) : db(database.getHandle()) {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS courses (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                institute TEXT NOT NULL
            );
        )";
        
        Database::Statement stmt(db, sql);
        sqlite3_step(stmt);
    }

    int addCourse(const course::Course& course) {
        const char* sql = R"(
            INSERT INTO courses (name, institute)
            VALUES (?, ?);
        )";
        
        Database::Statement stmt(db, sql);
        stmt.bind(1, course.getName());
        stmt.bind(2, course.getInstitute());
        
        if(sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        return sqlite3_last_insert_rowid(db);
    }

    bool exists(int courseId) {
        const char* sql = "SELECT 1 FROM courses WHERE id = ?;";
        Database::Statement stmt(db, sql);
        stmt.bind(1, courseId);

        return sqlite3_step(stmt) == SQLITE_ROW;
    }

    course::Course getCourse(int id) {
        const char* sql = "SELECT * FROM courses WHERE id = ?;";

        Database::Statement stmt(db, sql);
        stmt.bind(1, id);
        
        if(sqlite3_step(stmt) == SQLITE_ROW) {
            return course::Course(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
            );
        }
        throw std::runtime_error("Course not found");
    }
};

} // namespace database