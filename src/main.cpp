#include "database/database.hpp"
#include "ui/registration_menu.hpp"
#include <iostream>

int main() {
    try {
        database::Database db;
        menu::RegistrationMenu registration(db);
        
        int studentId = registration.registerStudent();
        if(studentId != -1) {
            std::cout << "Студент успешно зарегистрирован! ID: "  << studentId << "\n";
        }
    }
    catch(const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}