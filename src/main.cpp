#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <map>
#include <iomanip>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

namespace fs = std::filesystem;

class Course {

private:
    int id;
    std::string name;
    std::string institute;

public:
    Course(int id, const std::string& name, const std::string& institute)
        : id(id), name(name), institute(institute) {}

    inline const int getId() const { return id; }
    inline const std::string& getName() const { return name; }
    inline const std::string& getInstitute() const { return institute; }

    inline void setId(const int id_) { this->id = id_; };
    inline void setName(const std::string& name_) { this->name = name_; };
    inline void setInstitute(const std::string& institute_) { this->institute = institute_; };
};

class Teacher {

private:
    int id;
    std::string fio;
    std::string institute;
    std::string department;

public:

    Teacher(int id, const std::string& fio, const std::string& institute, const std::string& department)
        : id(id), fio(fio), institute(institute), department(department) {}

    inline const int getId() const { return id; }
    inline const std::string& getFio() const { return fio; }
    inline const std::string& getInstitute() const { return institute; }
    inline const std::string& getDepartment() const { return department; }

    inline void setId(const int id_) { this->id = id_; };
    inline void setFio(const std::string& fio_) { this->fio = fio_; };
    inline void setInstitute(const std::string& institute_) { this->institute = institute_; };
    inline void setDepartment(const std::string& department_) { this->department = department_; };
};

class Database {

private:
    std::string baseDir = "database";
    const std::string adminPassword = "admin123";

    void createDirIfNotExists() {
        if (!fs::exists(baseDir)) fs::create_directory(baseDir);
    }

    std::string getFilePath(const std::string& entity) { 
        return baseDir + "/" + entity + ".csv"; 
    }

    void initFile(const std::string& entity, const std::vector<std::string>& headers) {
        std::string path = getFilePath(entity);
        if (!fs::exists(path)) {
            std::ofstream file(path);
            if (file) {
                for (size_t i = 0; i < headers.size(); ++i) {
                    file << headers[i];
                    if (i != headers.size() - 1) file << ",";
                }
                file << "\n";
            }
        }
    }

public:
    struct Rating {
        int targetId;
        int rating;
    };

    Database() {
        createDirIfNotExists();
        initFile("students", {"id", "fio", "institute", "department", "course", "group", "record_book"});
        initFile("teachers", {"id", "fio", "institute", "department"});
        initFile("courses", {"id", "name", "institute"});
        initFile("ratings_courses", {"student_id", "course_id", "rating"});
        initFile("ratings_teachers", {"student_id", "teacher_id", "rating"});
    }

    bool authenticateAdmin(const std::string& password) {
        return password == adminPassword;
    }

    int getNextId(const std::string& entity) {
        std::ifstream file(getFilePath(entity));
        std::string line;
        int maxId = 0;
        std::getline(file, line);
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr;
            std::getline(ss, idStr, ',');
            try { maxId = std::max(maxId, std::stoi(idStr)); }
            catch (...) {}
        }

        return maxId + 1;
    }

    bool addStudent(const std::string& fio, const std::string& institute, const std::string& department,
                   int course, const std::string& group, const std::string& recordBook) {
        std::ofstream file(getFilePath("students"), std::ios::app);
        if (!file) return false;
        
        file << getNextId("students") << ","
             << fio << "," << institute << "," << department << ","
             << course << "," << group << "," << recordBook << "\n";

        return true;
    }

    bool addCourse(const std::string& name, const std::string& institute) {
        std::ofstream file(getFilePath("courses"), std::ios::app);
        if (!file) return false;
        
        file << getNextId("courses") << "," << name << "," << institute << "\n";

        return true;
    }

    bool addTeacher(const std::string& fio, const std::string& institute, const std::string& department) {
        std::ofstream file(getFilePath("teachers"), std::ios::app);
        if (!file) return false;
        
        file << getNextId("teachers") << "," << fio << "," << institute << "," << department << "\n";

        return true;
    }

    std::vector<Course> getAllCourses() {
        std::vector<Course> courses;
        std::ifstream file(getFilePath("courses"));
        std::string line;
        std::getline(file, line);
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, name, institute;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, institute, ',');
            courses.emplace_back(std::stoi(id), name, institute);
        }

        return courses;
    }

    std::vector<Teacher> getAllTeachers() {
        std::vector<Teacher> teachers;
        std::ifstream file(getFilePath("teachers"));
        std::string line;
        std::getline(file, line);
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, fio, institute, department;
            std::getline(ss, id, ',');
            std::getline(ss, fio, ',');
            std::getline(ss, institute, ',');
            std::getline(ss, department, ',');
            teachers.emplace_back(std::stoi(id), fio, institute, department);
        }

        return teachers;
    }

    bool courseExists(int courseId) {
        auto courses = getAllCourses();
        return std::any_of(courses.begin(), courses.end(),
            [courseId](const Course& c) { return c.getId() == courseId; });
    }

    bool teacherExists(int teacherId) {
        auto teachers = getAllTeachers();
        return std::any_of(teachers.begin(), teachers.end(),
            [teacherId](const Teacher& t) { return t.getId() == teacherId; });
    }

    bool addCourseRating(int studentId, int courseId, int rating) {
        if (!courseExists(courseId)) return false;
        
        std::ofstream file(getFilePath("ratings_courses"), std::ios::app);
        file << studentId << "," << courseId << "," << rating << "\n";

        return true;
    }

    bool addTeacherRating(int studentId, int teacherId, int rating) {
        if (!teacherExists(teacherId)) return false;
        
        std::ofstream file(getFilePath("ratings_teachers"), std::ios::app);
        file << studentId << "," << teacherId << "," << rating << "\n";
        return true;
    }

    std::vector<Rating> getCourseRatings(int studentId) {
        std::vector<Rating> ratings;
        std::ifstream file(getFilePath("ratings_courses"));
        std::string line;
        std::getline(file, line);
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string sId, cId, rating;
            std::getline(ss, sId, ',');
            std::getline(ss, cId, ',');
            std::getline(ss, rating, ',');
            
            if (std::stoi(sId) == studentId) {
                ratings.push_back({std::stoi(cId), std::stoi(rating)});
            }
        }
        return ratings;
    }

    std::vector<Rating> getTeacherRatings(int studentId) {
        std::vector<Rating> ratings;
        std::ifstream file(getFilePath("ratings_teachers"));
        std::string line;
        std::getline(file, line);
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string sId, tId, rating;
            std::getline(ss, sId, ',');
            std::getline(ss, tId, ',');
            std::getline(ss, rating, ',');
            
            if (std::stoi(sId) == studentId) {
                ratings.push_back({std::stoi(tId), std::stoi(rating)});
            }
        }
        return ratings;
    }

    std::vector<std::tuple<int, int, int>> getAllRatings() {
        std::vector<std::tuple<int, int, int>> ratings;
        
        // Оценки курсов
        std::ifstream coursesFile(getFilePath("ratings_courses"));
        std::string line;
        std::getline(coursesFile, line);
        while (std::getline(coursesFile, line)) {
            std::stringstream ss(line);
            std::string sId, cId, rating;
            std::getline(ss, sId, ',');
            std::getline(ss, cId, ',');
            std::getline(ss, rating, ',');
            ratings.emplace_back(std::stoi(sId), std::stoi(cId), std::stoi(rating));
        }

        // Оценки преподавателей
        std::ifstream teachersFile(getFilePath("ratings_teachers"));
        std::getline(teachersFile, line);
        while (std::getline(teachersFile, line)) {
            std::stringstream ss(line);
            std::string sId, tId, rating;
            std::getline(ss, sId, ',');
            std::getline(ss, tId, ',');
            std::getline(ss, rating, ',');
            ratings.emplace_back(std::stoi(sId), std::stoi(tId), std::stoi(rating));
        }

        return ratings;
    }
};

class AdminMenu {

private:
    Database& db;
    
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
                [id](const Course& c) { return c.getId() == id; });
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
                [id](const Teacher& t) { return t.getId() == id; });
            if (it != teachers.end()) {
                double avg = static_cast<double>(stats.first) / stats.second;
                std::cout << " " << std::left << std::setw(25) << it->getFio() 
                          << " | " << GREEN << "Средняя: " << std::fixed << std::setprecision(1) << avg
                          << RESET << " | " << BLUE << "Оценок: " << stats.second << RESET << "\n";
            }
        }
    }

public:
    AdminMenu(Database& db) : db(db) {}

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
    Database& db;
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
                [rating](const Course& c) { return c.getId() == rating.targetId; });
            if (it != courses.end()) {
                std::cout << " • " << std::left << std::setw(25) << it->getName()
                          << " [" << YELLOW << rating.rating << "/5" << RESET << "]\n";
            }
        }

        std::cout << UNDERLINE << "\nПреподаватели:" << RESET << "\n";
        for (const auto& rating : teacherRatings) {
            auto it = std::find_if(teachers.begin(), teachers.end(), 
                [rating](const Teacher& t) { return t.getId() == rating.targetId; });
            if (it != teachers.end()) {
                std::cout << " • " << std::left << std::setw(25) << it->getFio()
                          << " [" << YELLOW << rating.rating << "/5" << RESET << "]\n";
            }
        }
    }

public:
    RatingMenu(Database& db, int studentId) : db(db), studentId(studentId) {}

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
    Database& db;

    inline void printHeader(const std::string& text) {
        std::cout << BOLD << CYAN << "\n" << text << RESET << "\n";
    }

public:
    RegistrationMenu(Database& db) : db(db) {}

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
    Database db;
    
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