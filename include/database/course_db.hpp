#pragma once

#include "database.hpp"
#include "../classes/course.hpp"

namespace database {

class CourseDB {
private:
    sqlite3* db;
    
public:
    explicit CourseDB(const Database& database);

    ~CourseDB() = default;

    int addCourse(const course::Course& course);

    course::Course getCourse(int id);

}; // CourseDB

} // namespace database