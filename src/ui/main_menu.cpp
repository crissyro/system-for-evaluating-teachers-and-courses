#include "../../include/ui/main_menu.hpp"

#include <iostream>

#include "../../include/ui/admin_menu.hpp"
#include "../../include/ui/login_menu.hpp"
#include "../../include/ui/registration_menu.hpp"
#include "../../include/ui/student_menu.hpp"

namespace menu {

MainMenu::MainMenu(database::Database& database) : db(database) {}

void MainMenu::run() {
    int choice;
    while (true) {
        std::cout << BOLD << CYAN << "\nГлавное меню:\n"
                  << RESET << "1. Вход студента\n"
                  << "2. Вход администратора\n"
                  << "3. Регистрация студента\n"
                  << "0. Выход\n"
                  << "Выбор: ";

        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
                case 1: {
                    LoginMenu login(db);
                    int studentId = login.loginStudent();
                    if (studentId != -1) {
                        StudentMenu studentMenu(db, studentId);
                        studentMenu.show();
                    }
                    break;
                }

                case 2: {
                    LoginMenu login(db);
                    if (login.loginAdmin()) {
                        AdminMenu adminMenu(db);
                        adminMenu.show();
                    } else {
                        std::cout << RED << "Неверные данные!\n" << RESET;
                    }
                    break;
                }

                case 3: {
                    RegistrationMenu reg(db);
                    int id = reg.registerStudent();
                    if (id != -1) {
                        std::cout << GREEN << "Студент зарегистрирован! ID: " << id << RESET << "\n";
                    }
                    break;
                }

                case 0:
                    return;

                default:
                    std::cout << RED << "Неверный выбор!\n" << RESET;
            }
        } catch (const std::exception& e) {
            std::cout << RED << "Ошибка: " << e.what() << RESET << "\n";
        }
    }
}

}  // namespace menu