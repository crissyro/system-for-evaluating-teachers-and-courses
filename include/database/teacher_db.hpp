#pragma once

#include "database.hpp"
#include "../classes/teacher.hpp"

namespace database {

class TeacherDB {
private:
    sqlite3* db;
    
public:
    explicit TeacherDB(const Database& database);

    ~TeacherDB();

    int addTeacher(const teacher::Teacher& teacher);

    bool exists(int teacherId);

    teacher::Teacher getTeacher(int id);

}; // class Teacher

} // namespace database