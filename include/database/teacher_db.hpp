#pragma once

#include <vector>
#include "database.hpp"
#include "../classes/teacher.hpp"

namespace database {

class TeacherDB {
private:
    sqlite3* db;
    
public:
    explicit TeacherDB(const Database& database);

    ~TeacherDB() = default;

    int addTeacher(const teacher::Teacher& teacher);

    bool exists(int teacherId);

    std::vector<teacher::Teacher> getAllTeachers();

    teacher::Teacher getTeacher(int id);

}; // class Teacher

} // namespace database