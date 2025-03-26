#pragma once

#include "../classes/student.hpp"
#include "database.hpp"

namespace database {

class StudentDB {
 private:
  sqlite3* db;

 public:
  explicit StudentDB(const Database& database);

  ~StudentDB() = default;

  int addStudent(const student::Student& student);

  bool exists(const std::string& recordBook);

  int getStudentIdByRecordBook(const std::string& recordBook);

};  // class StudentDB

}  // namespace database