#include "../../include/ui/registration_menu.hpp"

#include <iostream>

#include "../../include/classes/student.hpp"
#include "../../include/database/student_db.hpp"

namespace menu
{

RegistrationMenu::RegistrationMenu(database::Database& database) : db(database) {}

int RegistrationMenu::registerStudent()
{
    std::string surname;
    std::string name;
    std::string patronymic;
    std::string institute;
    std::string department;
    std::string group;
    std::string recordBook;
    int course;

    std::cout << BOLD << CYAN << "\n=== Регистрация студента ===\n" << RESET;

    std::cout << "Фамилия: ";
    std::getline(std::cin, surname);

    std::cout << "Имя: ";
    std::getline(std::cin, name);

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

    try
    {
        database::StudentDB studentDB(db);

        if (studentDB.exists(recordBook))
        {
            std::cout << RED << "Ошибка: Зачетная книжка уже зарегистрирована!\n" << RESET;
            return -1;
        }

        student::Student newStudent(0, surname, name, patronymic, institute, department, course, group, recordBook);

        return studentDB.addStudent(newStudent);
    }
    catch (const std::exception& e)
    {
        std::cout << RED << "Ошибка: " << e.what() << RESET << "\n";
        return -1;
    }
}

}  // namespace menu