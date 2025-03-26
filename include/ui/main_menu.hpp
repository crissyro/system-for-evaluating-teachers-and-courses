#pragma once

#include "../database/database.hpp"
#include "colors.hpp"

namespace menu {

class MainMenu {
 private:
  database::Database& db;

 public:
  explicit MainMenu(database::Database& database);

  ~MainMenu() = default;

  void run();

};  // class MainMenu

}  // namespace menu