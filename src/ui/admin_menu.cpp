#include <iostream>

#include "../include/ui/admin_menu.hpp"
#include "../include/database/rating_db.hpp"
#include "../include/database/course_db.hpp"


namespace menu {

AdminMenu::AdminMenu(database::Database& database) : db(database) {}

void AdminMenu::showAllRatings() {
    database::RatingDB ratingDB(db);
    auto ratings = ratingDB.getAllRatings();
    
    std::cout << BOLD << YELLOW << "\n=== Все оценки ===\n" << RESET;
    for (const auto& r : ratings) {
        std::cout << "Студент ID: " << r.getStudentId()
             << " | " << (r.isCourseRating() ? "Курс ID: " : "Преподаватель ID: ")
             << r.getEntityId() << " | Оценка: " << r.getValue() << "/5\n";
    }
}

void AdminMenu::showStatistics() {
    database::RatingDB ratingDB(db);
    auto stats = ratingDB.getStatistics();
    
    std::cout << BOLD << CYAN << "\n=== Статистика ===\n" << RESET
         << "Средняя оценка курсов: " << stats.avgCourseRating << "/5\n"
         << "Средняя оценка преподавателей: " << stats.avgTeacherRating << "/5\n";
}

void AdminMenu::show() {
    int choice;
    while (true) {
        std::cout << BOLD << MAGENTA << "\nАдминистраторское меню:\n" << RESET
             << "1. Показать все оценки\n"
             << "2. Статистика оценок\n"
             << "0. Выход\n"
             << "Выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
                case 1: showAllRatings(); break;
                case 2: showStatistics(); break;
                case 0: return;
                default: std::cout << RED << "Неверный выбор!\n" << RESET;
            }
        } catch (const std::exception& e) {
            std::cout << RED << "Ошибка: " << e.what() << RESET << "\n";
        }
    }
}

} 