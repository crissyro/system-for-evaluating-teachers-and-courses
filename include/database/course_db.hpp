#pragma once

#include <vector>

#include "../classes/course.hpp"
#include "database.hpp"

namespace database {

class CourseDB {
 private:
  sqlite3* db;

 public:
  explicit CourseDB(const Database& database);

  ~CourseDB() = default;

  int addCourse(const course::Course& course);

  course::Course getCourse(int id);

  bool exists(int courseId);

  std::vector<course::Course> getAllCourses();

};  // CourseDB

}  // namespace database