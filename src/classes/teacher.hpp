#pragma once

#include <string>

namespace teacher {

class Teacher {
    int id;
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string institute;
    std::string department;

public:
    Teacher(int id, const std::string& lastName, const std::string& firstName,
           const std::string& patronymic, const std::string& institute, const std::string& department)
        : id(id), lastName(lastName), firstName(firstName), patronymic(patronymic), institute(institute),
          department(department) {}

    ~Teacher() = default;

    inline int getId() const { return id; }
    inline std::string getFullName() const { return lastName + " " + firstName + " " + patronymic; }
    inline std::string getLastName() const { return lastName; }
    inline std::string getFirstName() const { return firstName; }
    inline std::string getPatronymic() const { return patronymic; }
    inline std::string getInstitute() const { return institute; }
    inline std::string getDepartment() const { return department; }
};

} // namespace teacher