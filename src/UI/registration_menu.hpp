#pragma once

#include <iostream>
#include "colors.hpp"
#include "../database/database.hpp"
#include "../database/student_db.hpp"
#include "../classes/student.hpp"

namespace menu {

class RegistrationMenu {
    database::Database& db;
    database::StudentDB studentDB;
    
public:
    RegistrationMenu(database::Database& database) 
        : db(database), studentDB(database) {}

    int registerStudent() {
        std::cout << BOLD << CYAN << "\n=== РЕГИСТРАЦИЯ СТУДЕНТА ===" << RESET << "\n";
        
        std::string lastName, firstName, patronymic, 
                    institute, department, group, recordBook;
        int course;
        
        std::cout << "Фамилия: ";
        std::getline(std::cin, lastName);

        std::cout << "Имя: ";
        std::getline(std::cin, firstName);

        std::cout << "Отчество: ";
        std::getline(std::cin, patronymic);

        std::cout << "Институт: ";
        std::getline(std::cin, institute);

        std::cout << "Кафедра: ";
        std::getline(std::cin, department);

        std::cout << "Курс: ";
        std::cin >> course;

        std::cin.ignore();

        std::cout << "Группа: ";
        std::getline(std::cin, group);
        
        std::cout << "Номер зачетки: ";
        std::getline(std::cin, recordBook);

        if(studentDB.exists(recordBook)) {
            std::cerr << RED << "Ошибка: Студент с таким номером зачетки уже существует!\n" << RESET;
            return -1;
        }

        student::Student student(0, lastName, firstName, patronymic, 
                               institute, department, course, group, recordBook);

        int id = studentDB.addStudent(student);

        if(id != -1) {
            std::cout << GREEN << "Студент успешно зарегистрирован! ID: " << id << RESET << "\n";
        }

        return id;
    }
};

} // namespace menu