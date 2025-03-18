#pragma once

#include <string>

namespace student {

class Student {
private:
    int id;
    std::string surname;
    std::string name;
    std::string patronymic;
    std::string institute;
    std::string department;
    int course;
    std::string group;
    int recordBook;

public:
    Student(int id, const std::string& surname, const std::string& name,
           const std::string& patronymic, const std::string& institute,
           const std::string& department, int course, const std::string& group,
           const int& recordBook);

    inline int getId() const { return id; }

    inline std::string getSurname() const { return surname; }

    inline std::string getName() const { return name; }

    inline std::string getPatronymic() const { return patronymic; }

    inline std::string getInstitute() const { return institute; }

    inline  std::string getDepartment() const { return department; }

    inline int getCourse() const { return course; }

    inline std::string getGroup() const { return group; }

    inline int getRecordBook() const { return recordBook; }

    inline std::string getFullName() const {
        return surname + " " + name + " " + patronymic;
    }

}; // Student

} // namespace student