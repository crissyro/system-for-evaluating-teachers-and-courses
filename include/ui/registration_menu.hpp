#pragma once

#include "colors.hpp"
#include "../database/database.hpp"

namespace menu {

class RegistrationMenu {
private:
    database::Database& db;
    
public:
    explicit RegistrationMenu(database::Database& database);

    ~RegistrationMenu() = default;

    int registerStudent();

}; // class RegistrationMenu

} // namespace menu