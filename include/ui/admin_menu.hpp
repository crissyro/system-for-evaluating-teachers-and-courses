#pragma once

#include "colors.hpp"
#include "../database/database.hpp"

namespace menu {
    
class AdminMenu {
private:
    database::Database& db;
    
public:
    explicit AdminMenu(database::Database& database);

    ~AdminMenu() = default;

    void show();

    void showAllRatings();

    void showStatistics();

}; // AdminMenu

} // namespace menu