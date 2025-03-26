#include <iostream>

#include "../../include/ui/student_menu.hpp"
#include "../../include/database/rating_db.hpp"
#include "../../include/database/course_db.hpp"
#include "../../include/database/teacher_db.hpp"


namespace menu {

StudentMenu::StudentMenu(database::Database& database, int sid) 
    : db(database), studentId(sid) {}

void StudentMenu::printHeader(const std::string& title) {
    std::cout << BOLD << CYAN << "\n=== " << title << " ===\n" << RESET;
}

void StudentMenu::rateCourse() {
    printHeader("Оценка курса");
    database::CourseDB courseDB(db);
    auto courses = courseDB.getAllCourses();

    for (const auto& course : courses) {
        std::cout << course.getId() << ". " << course.getName() << "\n";
    }

    int courseId, rating;
    std::cout << "ID курса: ";
    std::cin >> courseId;

    database::RatingDB ratingDB(db);
    bool hasExistingRating = ratingDB.hasExistingRating(studentId, courseId, true);

    std::cout << "Оценка (1-5): ";
    std::cin >> rating;

    if (rating < 1 || rating > 5) {
        std::cout << RED << "Некорректная оценка!\n" << RESET;
        return;
    }

    if (ratingDB.addCourseRating(studentId, courseId, rating)) {
        std::cout << GREEN << "Оценка " 
                  << (hasExistingRating ? "обновлена" : "добавлена") 
                  << "!\n" << RESET;
    } else {
        std::cout << RED << "Ошибка!\n" << RESET;
    }
}

void StudentMenu::rateTeacher() {
    printHeader("Оценка преподавателя");
    database::TeacherDB teacherDB(db);
    auto teachers = teacherDB.getAllTeachers();

    for (const auto& teacher : teachers) {
        std::cout << teacher.getId() << ". " << teacher.getFullName() << "\n";
    }

    int teacherId, rating;
    std::cout << "ID преподавателя: ";
    std::cin >> teacherId;

    database::RatingDB ratingDB(db);
    bool hasExistingRating = ratingDB.hasExistingRating(studentId, teacherId, false);

    std::cout << "Оценка (1-5): ";
    std::cin >> rating;

    if (rating < 1 || rating > 5) {
        std::cout << RED << "Некорректная оценка!\n" << RESET;
        return;
    }

    if (ratingDB.addTeacherRating(studentId, teacherId, rating)) {
        std::cout << GREEN << "Оценка " 
                  << (hasExistingRating ? "обновлена" : "добавлена") 
                  << "!\n" << RESET;
    } else {
        std::cout << RED << "Ошибка!\n" << RESET;
    }
}

void StudentMenu::viewRatings() {
    database::RatingDB ratingDB(db);
    
    auto [courseRatings, teacherRatings] = ratingDB.getStudentRatings(studentId);
    
    std::cout << YELLOW << "\nОценки за курсы:\n" << RESET;

    for(const auto& [courseId, rating] : courseRatings) {
        std::cout << "Курс ID: " << courseId << ": " << rating << "/5\n";
    }
    
    std::cout << YELLOW << "\nОценки преподавателей:\n" << RESET;

    for(const auto& [teacherId, rating] : teacherRatings) {
        std::cout << "Преподаватель ID: " << teacherId << ": " << rating << "/5\n";
    }
}

void StudentMenu::show() {
    int choice;
    while (true) {
        std::cout << BOLD << MAGENTA << "\nМеню студента:\n" << RESET
             << "1. Оценить курс\n"
             << "2. Просмотреть оценки\n"
             << "3. Оценить преподавателя\n"
             << "0. Выход\n"
             << "Выбор: ";

        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
                case 1: rateCourse(); break;
                case 2: viewRatings(); break;
                case 3: rateTeacher(); break;
                case 0: return;
                default: std::cout << RED << "Неверный выбор!\n" << RESET;
            }
        } catch (const std::exception& e) {
            std::cout << RED << "Ошибка: " << e.what() << RESET << "\n";
        }
    }
}

}