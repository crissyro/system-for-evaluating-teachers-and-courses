#include "../../include/ui/login_menu.hpp"

#include <iostream>

#include "../../include/database/admin_db.hpp"
#include "../../include/database/student_db.hpp"

namespace menu
{

LoginMenu::LoginMenu(database::Database& database) : db(database) {}

int LoginMenu::loginStudent()
{
    std::string recordBook;
    std::cout << CYAN << "Введите номер зачетки: " << RESET;
    std::getline(std::cin, recordBook);

    database::StudentDB studentDB(db);
    if (studentDB.exists(recordBook))
    {
        return studentDB.getStudentIdByRecordBook(recordBook);
    }
    std::cout << RED << "Студент не найден!\n" << RESET;
    return -1;
}

bool LoginMenu::loginAdmin()
{
    std::string username;
    std::cout << CYAN << "Логин: " << RESET;

    std::getline(std::cin, username);

    std::string password;
    std::cout << CYAN << "Пароль: " << RESET;

    std::getline(std::cin, password);

    database::AdminDB adminDB(db);

    return adminDB.checkCredentials(username, password);
}

}  // namespace menu