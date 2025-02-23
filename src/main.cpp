#include <iostream>
#include <map>

#include "database/database.hpp"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

class AdminMenu {

private:
    file_database::Database& db;
    
    void printHeader(const std::string& text) {
        std::cout << BOLD << CYAN << "\n" << text << RESET << "\n";
    }

    void showCourses() {
        auto courses = db.getAllCourses();
        printHeader("Список курсов:");
        for (const auto& c : courses) {
            std::cout << " " << YELLOW << std::setw(3) << c.getId() << RESET
                      << " | " << std::left << std::setw(30) << c.getName() 
                      << " | " << c.getInstitute() << "\n";
        }
    }

    void showTeachers() {
        auto teachers = db.getAllTeachers();
        printHeader("Список преподавателей:");
        for (const auto& t : teachers) {
            std::cout << " " << YELLOW << std::setw(3) << t.getId() << RESET
                      << " | " << std::left << std::setw(25) << t.getFio() 
                      << " | " << std::setw(15) << t.getDepartment()
                      << " | " << t.getInstitute() << "\n";
        }
    }

    void showAllRatings() {
         auto ratings = db.getAllRatings();
        auto courses = db.getAllCourses();
        auto teachers = db.getAllTeachers();

        std::map<int, std::pair<int, int>> courseStats;
        std::map<int, std::pair<int, int>> teacherStats;

        for (const auto& [sId, targetId, rating] : ratings) {
            if (db.courseExists(targetId)) {
                courseStats[targetId].first += rating;
                courseStats[targetId].second++;
            } else if (db.teacherExists(targetId)) {
                teacherStats[targetId].first += rating;
                teacherStats[targetId].second++;
            }
        }

        printHeader("Статистика оценок");

        std::cout << UNDERLINE << "Курсы:" << RESET << "\n";
        for (const auto& [id, stats] : courseStats) {
            auto it = std::find_if(courses.begin(), courses.end(), 
                [id](const course::Course& c) { return c.getId() == id; });
            if (it != courses.end()) {
                double avg = static_cast<double>(stats.first) / stats.second;
                std::cout << " " << std::left << std::setw(30) << it->getName() 
                        << " | " << GREEN << "Средняя: " << std::fixed << std::setprecision(1) << avg
                        << RESET << " | " << BLUE << "Оценок: " << stats.second << RESET << "\n";
            }
        }

        std::cout << UNDERLINE << "\nПреподаватели:" << RESET << "\n";
        for (const auto& [id, stats] : teacherStats) {
            auto it = std::find_if(teachers.begin(), teachers.end(), 
                [id](const teacher::Teacher& t) { return t.getId() == id; });
            if (it != teachers.end()) {
                double avg = static_cast<double>(stats.first) / stats.second;
                std::cout << " " << std::left << std::setw(25) << it->getFio() 
                          << " | " << GREEN << "Средняя: " << std::fixed << std::setprecision(1) << avg
                          << RESET << " | " << BLUE << "Оценок: " << stats.second << RESET << "\n";
            }
        }
    }

public:
    AdminMenu(file_database::Database& db) : db(db) {}

    void show() {
        int choice;
        do {
            std::cout << BOLD << MAGENTA << "\n=== АДМИНИСТРАТОРСКОЕ МЕНЮ ===" << RESET
                      << "\n1. Добавить курс"
                      << "\n2. Добавить преподавателя"
                      << "\n3. Просмотр курсов"
                      << "\n4. Просмотр преподавателей"
                      << "\n5. Статистика оценок"
                      << "\n6. Выход"
                      << "\nВыберите действие: ";
            
            std::cin >> choice;
            std::cin.ignore();

            switch(choice) {
                case 1: {
                    std::string name, institute;
                    std::cout << "Название курса: ";
                    std::getline(std::cin, name);
                    std::cout << "Институт: ";
                    std::getline(std::cin, institute);
                    if (db.addCourse(name, institute)) {
                        std::cout << GREEN << "Курс успешно добавлен!\n" << RESET;
                    }
                    break;
                }

                case 2: {
                    std::string fio, institute, department;
                    std::cout << "ФИО преподавателя: ";
                    std::getline(std::cin, fio);
                    std::cout << "Институт: ";
                    std::getline(std::cin, institute);
                    std::cout << "Кафедра: ";
                    std::getline(std::cin, department);
                    if (db.addTeacher(fio, institute, department)) {
                        std::cout << GREEN << "Преподаватель успешно добавлен!\n" << RESET;
                    }
                    break;
                }

                case 3: showCourses(); break;

                case 4: showTeachers(); break;

                case 5: showAllRatings(); break;

                case 6: return;

                default: std::cout << RED << "Неверный выбор!\n" << RESET;
            }
        } while(true);
    }
};

class RatingMenu {

private:
    file_database::Database& db;
    int studentId;

    inline void printHeader(const std::string& text) {
        std::cout << BOLD << CYAN << "\n" << text << RESET << "\n";
    }

    inline void showCourses() {
        auto courses = db.getAllCourses();

        printHeader("Доступные курсы:");

        for (const auto& c : courses) {
            std::cout << " " << YELLOW << std::setw(3) << c.getId() << RESET
                      << " | " << c.getName() << " (" << c.getInstitute() << ")\n";
        }
    }

    inline void showTeachers() {
        auto teachers = db.getAllTeachers();

        printHeader("Доступные преподаватели:");

        for (const auto& t : teachers) {
            std::cout << " " << YELLOW << std::setw(3) << t.getId() << RESET
                      << " | " << t.getFio() << " (" << t.getDepartment() << ")\n";
        }
    }

    void showStudentRatings() {
        auto courseRatings = db.getCourseRatings(studentId);
        auto teacherRatings = db.getTeacherRatings(studentId);
        auto courses = db.getAllCourses();
        auto teachers = db.getAllTeachers();

        printHeader("Ваши оценки");
        
        std::cout << UNDERLINE << "Курсы:" << RESET << "\n";
        for (const auto& rating : courseRatings) {
            auto it = std::find_if(courses.begin(), courses.end(), 
                [rating](const course::Course& c) { return c.getId() == rating.targetId; });
            if (it != courses.end()) {
                std::cout << " • " << std::left << std::setw(25) << it->getName()
                          << " [" << YELLOW << rating.rating << "/5" << RESET << "]\n";
            }
        }

        std::cout << UNDERLINE << "\nПреподаватели:" << RESET << "\n";
        for (const auto& rating : teacherRatings) {
            auto it = std::find_if(teachers.begin(), teachers.end(), 
                [rating](const teacher::Teacher& t) { return t.getId() == rating.targetId; });
            if (it != teachers.end()) {
                std::cout << " • " << std::left << std::setw(25) << it->getFio()
                          << " [" << YELLOW << rating.rating << "/5" << RESET << "]\n";
            }
        }
    }

public:
    RatingMenu(file_database::Database& db, int studentId) : db(db), studentId(studentId) {}

    void show() {
        int choice;
        do {
            std::cout << BOLD << MAGENTA << "\n=== МЕНЮ ОЦЕНКИ ===" << RESET
                      << "\n1. Оценить курс"
                      << "\n2. Оценить преподавателя"
                      << "\n3. Мои оценки"
                      << "\n4. Выход"
                      << "\nВыберите действие: ";
            
            std::cin >> choice;
            std::cin.ignore();

            switch(choice) {
                case 1: {
                    showCourses();
                    int courseId, rating;
                    std::cout << "Введите ID курса: ";
                    std::cin >> courseId;
                    std::cout << "Оценка (1-5): ";
                    std::cin >> rating;
                    if (rating < 1 || rating > 5) {
                        std::cout << RED << "Некорректная оценка!\n" << RESET;
                        break;
                    }
                    if (db.addCourseRating(studentId, courseId, rating)) {
                        std::cout << GREEN << "Оценка добавлена!\n" << RESET;
                    } else {
                        std::cout << RED << "Ошибка при добавлении оценки!\n" << RESET;
                    }
                    break;
                }

                case 2: {
                    showTeachers();
                    int teacherId, rating;
                    std::cout << "Введите ID преподавателя: ";
                    std::cin >> teacherId;
                    std::cout << "Оценка (1-5): ";
                    std::cin >> rating;
                    if (rating < 1 || rating > 5) {
                        std::cout << RED << "Некорректная оценка!\n" << RESET;
                        break;
                    }
                    if (db.addTeacherRating(studentId, teacherId, rating)) {
                        std::cout << GREEN << "Оценка добавлена!\n" << RESET;
                    } else {
                        std::cout << RED << "Ошибка при добавлении оценки!\n" << RESET;
                    }
                    break;
                }
                case 3: showStudentRatings(); break;

                case 4: return;

                default: std::cout << RED << "Неверный выбор!\n" << RESET;
            }
        } while(true);
    }
};

class RegistrationMenu {
    file_database::Database& db;

    inline void printHeader(const std::string& text) {
        std::cout << BOLD << CYAN << "\n" << text << RESET << "\n";
    }

public:
    RegistrationMenu(file_database::Database& db) : db(db) {}

    int registerStudent() {
        std::string fio, institute, department, group, recordBook;
        int course;

        printHeader("РЕГИСТРАЦИЯ СТУДЕНТА");
        std::cout << "ФИО: "; std::getline(std::cin, fio);
        std::cout << "Институт: "; std::getline(std::cin, institute);
        std::cout << "Кафедра: "; std::getline(std::cin, department);
        std::cout << "Курс: "; std::cin >> course; std::cin.ignore();
        std::cout << "Группа: "; std::getline(std::cin, group);
        std::cout << "Номер зачетки: "; std::getline(std::cin, recordBook);

        if (db.addStudent(fio, institute, department, course, group, recordBook)) {
            std::cout << GREEN << "\nРегистрация прошла успешно!\n" << RESET;
            return db.getNextId("students") - 1;
        }

        std::cout << RED << "\nОшибка регистрации!\n" << RESET;

        return -1;
    }
};

class MainMenu {
    file_database::Database db;
    
    inline void adminLogin() {
        std::string password;
        std::cout << "Введите пароль администратора: ";
        std::getline(std::cin, password);
        
        if (db.authenticateAdmin(password)) {
            AdminMenu(db).show();
        } else {
            std::cout << RED << "Неверный пароль!\n" << RESET;
        }
    }

public:
    void run() {
        int choice;
        do {
            std::cout << BOLD << MAGENTA << "\n=== ГЛАВНОЕ МЕНЮ ===" << RESET
                      << "\n1. Регистрация студента"
                      << "\n2. Вход администратора"
                      << "\n3. Выход"
                      << "\nВыберите действие: ";
            
            std::cin >> choice;
            std::cin.ignore();

            switch(choice) {
                case 1: {
                    RegistrationMenu reg(db);
                    int studentId = reg.registerStudent();
                    if (studentId != -1) {
                        RatingMenu(db, studentId).show();
                    }
                    break;
                }

                case 2: adminLogin(); break;

                case 3: return;

                default: std::cout << RED << "Неверный выбор!\n" << RESET;
            }
        } while(true);
    }
};

int main() {
    MainMenu menu;

    menu.run();

    return 0;
}