#include <iostream>
#include "ui/colors.hpp"
#include "database/database.hpp"
#include "ui/registration_menu.hpp"
#include "ui/admin_menu.hpp"


void showMainMenu() {
    std::cout << BOLD << MAGENTA << "\n=== ГЛАВНОЕ МЕНЮ ===" << RESET
              << "\n" << YELLOW << "1" << RESET << " - Регистрация студента"
              << "\n" << YELLOW << "2" << RESET << " - Регистрация администратора"
              << "\n" << YELLOW << "3" << RESET << " - Вход"
              << "\n" << YELLOW << "0" << RESET << " - Выход"
              << "\n\nВыберите действие: ";
}

int main() {
    try {
        database::Database db;
        
        while(true) {
            showMainMenu();
            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch(choice) {
                case 1: {
                    menu::RegistrationMenu reg(db);
                    reg.registerStudent();
                    break;
                }

                case 2: {
                    menu::AdminRegistrationMenu adminReg(db);
                    adminReg.registerAdmin();
                    break;
                }

                case 3: {
                    // TODO: Вход в систему
                    break;
                }

                case 0:
                    return 0;
                default:
                    std::cout << RED << "Неверный выбор!" << RESET << "\n";
            }
        }
    } catch(const std::exception& e) {
        std::cerr << RED << "Критическая ошибка: " << e.what() << RESET << "\n";
        return 1;
    }

    return 0;
}