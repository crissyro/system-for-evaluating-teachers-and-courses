#pragma once

#include <iostream>
#include "colors.hpp"
#include "../database/database.hpp"
#include "../database/admin_db.hpp"


namespace menu {

class AdminRegistrationMenu {
    database::Database& db;
    database::AdminDB adminDB;
    
public:
    AdminRegistrationMenu(database::Database& database) 
        : db(database), adminDB(database) {}

    bool registerAdmin() {
        std::cout << BOLD << CYAN << "\n=== РЕГИСТРАЦИЯ АДМИНИСТРАТОРА ===" << RESET << "\n";
        
        std::string username, password;
        
        std::cout << "Введите логин: ";
        std::getline(std::cin, username);
        
        if(adminDB.adminExists(username)) {
            std::cerr << RED << "Ошибка: Администратор с таким логином уже существует!\n" << RESET;
            return false;
        }
        
        std::cout << "Введите пароль: ";
        std::getline(std::cin, password);
        
        if(password.empty()) {
            std::cerr << RED << "Ошибка: Пароль не может быть пустым!\n" << RESET;
            return false;
        }
        
        if(adminDB.addAdmin(username, password)) {
            std::cout << GREEN << "Администратор успешно зарегистрирован!\n" << RESET;
            return true;
        }
        
        std::cerr << RED << "Ошибка при регистрации администратора!\n" << RESET;
        return false;
    }
};

} // namespace menu