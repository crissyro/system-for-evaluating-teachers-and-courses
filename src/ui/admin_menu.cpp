#include "../../include/ui/admin_menu.hpp"

#include <iostream>

#include "../../include/database/course_db.hpp"
#include "../../include/database/rating_db.hpp"
#include "../../include/database/teacher_db.hpp"

namespace menu
{

AdminMenu::AdminMenu(database::Database& database) : db(database) {}

void AdminMenu::showAllRatings()
{
    database::RatingDB ratingDB(db);
    auto ratings = ratingDB.getAllRatings();

    std::cout << BOLD << YELLOW << "\n=== Все оценки ===\n" << RESET;
    for (const auto& r : ratings)
    {
        std::cout << "Студент ID: " << r.getStudentId() << " | "
                  << (r.isCourseRating() ? "Курс ID: " : "Преподаватель ID: ") << r.getEntityId()
                  << " | Оценка: " << r.getValue() << "/5\n";
    }
}

void AdminMenu::showStatistics()
{
    database::RatingDB ratingDB(db);
    database::CourseDB courseDB(db);
    database::TeacherDB teacherDB(db);

    auto stats = ratingDB.getStatistics();

    std::cout << BOLD << CYAN << "\n=== Статистика по курсам ===\n" << RESET;
    for (const auto& [courseId, avg] : stats.courseStats)
    {
        try
        {
            auto course = courseDB.getCourse(courseId);
            std::cout << course.getName() << " (ID: " << courseId << "): " << avg << "/5\n";
        }
        catch (...)
        {
            std::cout << "Курс ID:" << courseId << " (удален): " << avg << "/5\n";
        }
    }

    std::cout << BOLD << CYAN << "\n=== Статистика по преподавателям ===\n" << RESET;
    for (const auto& [teacherId, avg] : stats.teacherStats)
    {
        try
        {
            auto teacher = teacherDB.getTeacher(teacherId);
            std::cout << teacher.getFullName() << " (ID: " << teacherId << "): " << avg << "/5\n";
        }
        catch (...)
        {
            std::cout << "Преподаватель ID:" << teacherId << " (удален): " << avg << "/5\n";
        }
    }
}

void AdminMenu::show()
{
    int choice;
    while (true)
    {
        std::cout << BOLD << MAGENTA << "\nАдминистраторское меню:\n"
                  << RESET << "1. Показать все оценки\n"
                  << "2. Статистика оценок\n"
                  << "3. Добавить курс\n"
                  << "4. Добавить преподавателя\n"
                  << "0. Выход\n"
                  << "Выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        try
        {
            switch (choice)
            {
                case 1:
                    showAllRatings();
                    break;
                case 2:
                    showStatistics();
                    break;
                case 3:
                    addCourse();
                    break;
                case 4:
                    addTeacher();
                    break;
                case 0:
                    return;
                default:
                    std::cout << RED << "Неверный выбор!\n" << RESET;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << RED << "Ошибка: " << e.what() << RESET << "\n";
        }
    }
}

void AdminMenu::addCourse()
{
    std::cout << BOLD << CYAN << "\nДобавление нового курса\n" << RESET;

    std::string name, institute;
    std::cout << "Название курса: ";
    std::getline(std::cin, name);

    std::cout << "Институт: ";
    std::getline(std::cin, institute);

    try
    {
        database::CourseDB courseDB(db);
        int id = courseDB.addCourse(course::Course(0, name, institute));
        std::cout << GREEN << "Курс добавлен! ID: " << id << RESET << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << RED << "Ошибка: " << e.what() << RESET << "\n";
    }
}

void AdminMenu::addTeacher()
{
    std::cout << BOLD << CYAN << "\nДобавление преподавателя\n" << RESET;

    std::string surname, name, patronymic, institute, department;
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

    try
    {
        database::TeacherDB teacherDB(db);
        int id = teacherDB.addTeacher(teacher::Teacher(0, surname, name, patronymic, institute, department));
        std::cout << GREEN << "Преподаватель добавлен! ID: " << id << RESET << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << RED << "Ошибка: " << e.what() << RESET << "\n";
    }
}

}  // namespace menu