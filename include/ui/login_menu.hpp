#pragma once

#include "../database/admin_db.hpp"
#include "../database/database.hpp"
#include "../database/student_db.hpp"
#include "colors.hpp"

namespace menu {

class LoginMenu {
 private:
  database::Database& db;

 public:
  LoginMenu(database::Database& database);

  ~LoginMenu() = default;

  int loginStudent();

  bool loginAdmin();
};

}  // namespace menu