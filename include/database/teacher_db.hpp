#pragma once

#include <vector>

#include "../classes/teacher.hpp"
#include "database.hpp"

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

};  // class Teacher

}  // namespace database