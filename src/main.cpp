#include <iostream>

#include "../include/database/database.hpp"
#include "../include/ui/main_menu.hpp"

int main() {
  try {
    database::Database db;

    menu::MainMenu mainMenu(db);
    mainMenu.run();

    std::cout << GREEN << "Программа завершена." << RESET << std::endl;

    return 0;

  } catch (const std::exception& e) {
    std::cerr << RED << "\nКритическая ошибка: " << e.what() << RESET
              << std::endl;
    return 1;
  }
}