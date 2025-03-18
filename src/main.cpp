#include "../include/database/database.hpp"
#include "menu/main_menu.hpp"
#include <iostream>


int main() {
    try {
        database::Database db;
        menu::MainMenu mainMenu(db);
        mainMenu.run();
    } catch(const std::exception& e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}