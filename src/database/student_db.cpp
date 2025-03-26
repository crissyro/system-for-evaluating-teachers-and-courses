#include "../../include/database/student_db.hpp"

namespace database {

StudentDB::StudentDB(const Database& database) : db(database.getHandle()) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            surname TEXT NOT NULL,
            name TEXT NOT NULL,
            patronymic TEXT,
            institute TEXT NOT NULL,
            department TEXT NOT NULL,
            course INTEGER NOT NULL,
            group_name TEXT NOT NULL,
            record_book INTEGER UNIQUE NOT NULL
        );)";

    Database::Statement stmt(db, sql);
    sqlite3_step(stmt);
}

int StudentDB::addStudent(const student::Student& student) {
    const char* sql = R"(
        INSERT INTO students 
        (surname, name, patronymic, institute, 
         department, course, group_name, record_book)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?);)";

    Database::Statement stmt(db, sql);
    stmt.bind(1, student.getSurname());
    stmt.bind(2, student.getName());
    stmt.bind(3, student.getPatronymic());
    stmt.bind(4, student.getInstitute());
    stmt.bind(5, student.getDepartment());
    stmt.bind(6, student.getCourse());
    stmt.bind(7, student.getGroup());
    stmt.bind(8, student.getRecordBook());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Ошибка регистрации студента");
    }

    return sqlite3_last_insert_rowid(db);
}

bool StudentDB::exists(const std::string& recordBook) {
    const char* sql = "SELECT 1 FROM students WHERE record_book = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, recordBook);

    return sqlite3_step(stmt) == SQLITE_ROW;
}

int StudentDB::getStudentIdByRecordBook(const std::string& recordBook) {
    const char* sql = "SELECT id FROM students WHERE record_book = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, recordBook);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        return sqlite3_column_int(stmt, 0);
    }

    return -1;
}

}  // namespace database