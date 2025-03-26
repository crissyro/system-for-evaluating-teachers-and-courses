#pragma once

#include "../database/database.hpp"
#include "colors.hpp"

namespace menu {

class RegistrationMenu {
 private:
  database::Database& db;

 public:
  explicit RegistrationMenu(database::Database& database);

  ~RegistrationMenu() = default;

  int registerStudent();

};  // class RegistrationMenu

}  // namespace menu