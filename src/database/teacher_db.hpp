#pragma once

#include "database.hpp"
#include "../classes/teacher.hpp"

namespace database {

class TeacherDB {
    sqlite3* db;
    
public:
    explicit TeacherDB(const Database& database) : db(database.getHandle()) {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS teachers (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                last_name TEXT NOT NULL,
                first_name TEXT NOT NULL,
                patronymic TEXT,
                institute TEXT NOT NULL,
                department TEXT NOT NULL
            );
        )";
        
        Database::Statement stmt(db, sql);
        sqlite3_step(stmt);
    }

    int addTeacher(const teacher::Teacher& teacher) {
        const char* sql = R"(
            INSERT INTO teachers 
            (last_name, first_name, patronymic, institute, department)
            VALUES (?, ?, ?, ?, ?);
        )";
        
        Database::Statement stmt(db, sql);
        stmt.bind(1, teacher.getLastName());
        stmt.bind(2, teacher.getFirstName());
        stmt.bind(3, teacher.getPatronymic());
        stmt.bind(4, teacher.getInstitute());
        stmt.bind(5, teacher.getDepartment());
        
        if(sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        return sqlite3_last_insert_rowid(db);
    }

    bool exists(int teacherId) {
        const char* sql = "SELECT 1 FROM teachers WHERE id = ?;";
        Database::Statement stmt(db, sql);
        stmt.bind(1, teacherId);

        return sqlite3_step(stmt) == SQLITE_ROW;
    }

    teacher::Teacher getTeacher(int id) {
        const char* sql = "SELECT * FROM teachers WHERE id = ?;";

        Database::Statement stmt(db, sql);
        stmt.bind(1, id);
        
        if(sqlite3_step(stmt) == SQLITE_ROW) {
            return teacher::Teacher(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))
            );
        }
        throw std::runtime_error("Teacher not found");
    }
};

} // namespace database