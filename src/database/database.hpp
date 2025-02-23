#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

#include "../classes/course.hpp"
#include "../classes/teacher.hpp"

namespace fs = std::filesystem;

namespace file_database {

class Database {

private:
    std::string baseDir = "database";
    const std::string adminPassword = "admin123";

    void createDirIfNotExists() {
        if (!fs::exists(baseDir)) fs::create_directory(baseDir);
    }

    inline std::string getFilePath(const std::string& entity) { 
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

    std::vector<course::Course> getAllCourses() {
        std::vector<course::Course> courses;
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

    std::vector<teacher::Teacher> getAllTeachers() {
        std::vector<teacher::Teacher> teachers;
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
            [courseId](const course::Course& c) { return c.getId() == courseId; });
    }

    bool teacherExists(int teacherId) {
        auto teachers = getAllTeachers();
        return std::any_of(teachers.begin(), teachers.end(),
            [teacherId](const teacher::Teacher& t) { return t.getId() == teacherId; });
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
    
}; // end namespace file_database