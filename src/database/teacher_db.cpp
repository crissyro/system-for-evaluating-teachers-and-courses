#include "../../include/database/teacher_db.hpp"


namespace database {

TeacherDB::TeacherDB(const Database& database) : db(database.getHandle()) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS teachers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            surname TEXT NOT NULL,
            name TEXT NOT NULL,
            patronymic TEXT,
            institute TEXT NOT NULL,
            department TEXT NOT NULL
        );)";

    Database::Statement stmt(db, sql);
    sqlite3_step(stmt);
}

int TeacherDB::addTeacher(const teacher::Teacher& teacher) {
    const char* sql = R"(
        INSERT INTO teachers 
        (surname, name, patronymic, institute, department)
        VALUES (?, ?, ?, ?, ?);)";
    
    Database::Statement stmt(db, sql);
    stmt.bind(1, teacher.getSurname());
    stmt.bind(2, teacher.getName());
    stmt.bind(3, teacher.getPatronymic());
    stmt.bind(4, teacher.getInstitute());
    stmt.bind(5, teacher.getDepartment());
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Ошибка добавления преподавателя");
    }

    return sqlite3_last_insert_rowid(db);
}

bool TeacherDB::exists(int teacherId) {
    const char* sql = "SELECT 1 FROM teachers WHERE id = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, teacherId);

    return sqlite3_step(stmt) == SQLITE_ROW;
}

teacher::Teacher TeacherDB::getTeacher(int id) {
    const char* sql = "SELECT * FROM teachers WHERE id = ?;";
    
    Database::Statement stmt(db, sql);
    stmt.bind(1, id);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        return teacher::Teacher(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))
        );
    }

    throw std::runtime_error("Преподаватель не найден");
}

std::vector<teacher::Teacher> TeacherDB::getAllTeachers() {
    std::vector<teacher::Teacher> teachers;
    const char* sql = "SELECT * FROM teachers;";
    
    Database::Statement stmt(db, sql);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* patronymicPtr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string patronymic = patronymicPtr ? patronymicPtr : "";

        teachers.emplace_back(
            sqlite3_column_int(stmt, 0), 
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)), 
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)), 
            patronymic,
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)), 
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5))  
        );
    }
    
    return teachers;
}

} 