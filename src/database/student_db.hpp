#pragma once

#include "database.hpp"
#include "../classes/student.hpp"

namespace database {

class StudentDB {
    sqlite3* db;
    
public:
    explicit StudentDB(const Database& database) : db(database.getHandle()) {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS students (
                id INT PRIMARY KEY AUTOINCREMENT,
                last_name VARCHAR(128) NOT NULL,
                first_name VARCHAR(64) NOT NULL,
                patronymic VARCHAR(128),
                institute VARCHAR(256) NOT NULL,
                department VARCHAR(256) NOT NULL,
                course UNSIGNED SMALLINT NOT NULL,
                group_name VARCHAR(8) NOT NULL,
                record_book UNSIGNED INT UNIQUE NOT NULL
            );
        )";
        Database::Statement stmt(db, sql);
        sqlite3_step(stmt);
    }

    int addStudent(const student::Student& student) {
        const char* sql = R"(
            INSERT INTO students 
            (last_name, first_name, patronymic, institute, 
             department, course, group_name, record_book)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?);
        )";
        
        Database::Statement stmt(db, sql);
        stmt.bind(1, student.getLastName());
        stmt.bind(2, student.getFirstName());
        stmt.bind(3, student.getPatronymic());
        stmt.bind(4, student.getInstitute());
        stmt.bind(5, student.getDepartment());
        stmt.bind(6, student.getCourse());
        stmt.bind(7, student.getGroup());
        stmt.bind(8, student.getRecordBook());
        
        if(sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        return sqlite3_last_insert_rowid(db);
    }

    bool exists(const std::string& recordBook) {
        const char* sql = "SELECT 1 FROM students WHERE record_book = ?;";
        Database::Statement stmt(db, sql);
        stmt.bind(1, recordBook);
        return sqlite3_step(stmt) == SQLITE_ROW;
    }
};

} // namespace database