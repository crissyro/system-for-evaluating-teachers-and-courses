#pragma once

#include "colors.hpp"
#include "../database/database.hpp"

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

} // namespace menu