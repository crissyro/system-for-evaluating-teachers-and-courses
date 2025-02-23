#pragma once

#include "database.hpp"
#include <vector>

namespace database {

class RatingDB {
    sqlite3* db;
    
public:
    explicit RatingDB(const Database& database) : db(database.getHandle()) {
        const char* coursesSql = R"(
            CREATE TABLE IF NOT EXISTS course_ratings (
                student_id INTEGER NOT NULL,
                course_id INTEGER NOT NULL,
                rating INTEGER CHECK(rating BETWEEN 1 AND 5),
                FOREIGN KEY(student_id) REFERENCES students(id),
                FOREIGN KEY(course_id) REFERENCES courses(id)
            );
        )";
        
        const char* teachersSql = R"(
            CREATE TABLE IF NOT EXISTS teacher_ratings (
                student_id INTEGER NOT NULL,
                teacher_id INTEGER NOT NULL,
                rating INTEGER CHECK(rating BETWEEN 1 AND 5),
                FOREIGN KEY(student_id) REFERENCES students(id),
                FOREIGN KEY(teacher_id) REFERENCES teachers(id)
            );
        )";
        
        Database::Statement coursesStmt(db, coursesSql);
        Database::Statement teachersStmt(db, teachersSql);
        sqlite3_step(coursesStmt);
        sqlite3_step(teachersStmt);
    }

    bool addCourseRating(int studentId, int courseId, int rating) {
        const char* sql = R"(
            INSERT INTO course_ratings 
            (student_id, course_id, rating)
            VALUES (?, ?, ?);
        )";
        
        Database::Statement stmt(db, sql);
        stmt.bind(1, studentId);
        stmt.bind(2, courseId);
        stmt.bind(3, rating);
        
        return sqlite3_step(stmt) == SQLITE_DONE;
    }

    bool addTeacherRating(int studentId, int teacherId, int rating) {
        const char* sql = R"(
            INSERT INTO teacher_ratings 
            (student_id, teacher_id, rating)
            VALUES (?, ?, ?);
        )";
        
        Database::Statement stmt(db, sql);
        stmt.bind(1, studentId);
        stmt.bind(2, teacherId);
        stmt.bind(3, rating);
        
        return sqlite3_step(stmt) == SQLITE_DONE;
    }

    std::vector<std::pair<int, int>> getCourseRatings(int studentId) {
        std::vector<std::pair<int, int>> ratings;

        const char* sql = "SELECT course_id, rating FROM course_ratings WHERE student_id = ?;";
        
        Database::Statement stmt(db, sql);
        stmt.bind(1, studentId);
        
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            ratings.emplace_back(
                sqlite3_column_int(stmt, 0),
                sqlite3_column_int(stmt, 1)
            );
        }

        return ratings;
    }

    std::vector<std::pair<int, int>> getTeacherRatings(int studentId) {
        std::vector<std::pair<int, int>> ratings;

        const char* sql = "SELECT teacher_id, rating FROM teacher_ratings WHERE student_id = ?;";
        
        Database::Statement stmt(db, sql);
        stmt.bind(1, studentId);
        
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            ratings.emplace_back(
                sqlite3_column_int(stmt, 0),
                sqlite3_column_int(stmt, 1)
            );
        }

        return ratings;
    }
};

} // namespace database