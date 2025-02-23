#pragma once

#include <string>

namespace student {

class Student {
private:
    int id;
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string institute;
    std::string department;
    int course;
    std::string group;
    std::string recordBook;

public:
    Student(int id, const std::string& lastName, const std::string& firstName,
           const std::string& patronymic, const std::string& institute,
           const std::string& department, int course, const std::string& group,
           const std::string& recordBook) : id(id), lastName(lastName), firstName(firstName),
          patronymic(patronymic), institute(institute), department(department), course(course),
          group(group), recordBook(recordBook) {}

    ~Student() = default;

    inline int getId() const { return id; }
    inline std::string getFullName() const { return lastName + " " + firstName + " " + patronymic; }
    inline std::string getLastName() const { return lastName; }
    inline std::string getFirstName() const { return firstName; }
    inline std::string getPatronymic() const { return patronymic; }
    inline std::string getInstitute() const { return institute; }
    inline std::string getDepartment() const { return department; }
    inline int getCourse() const { return course; }
    inline std::string getGroup() const { return group; }
    inline std::string getRecordBook() const { return recordBook; }
};

} // namespace student