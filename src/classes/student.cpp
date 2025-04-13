#include "../../include/classes/student.hpp"

namespace student {

Student::Student(const std::string& surname, const std::string& name, const std::string& patronymic,
                 const std::string& institute, const std::string& department, int course, const std::string& group,
                 const std::string& recordBook)
    : id(0),
      surname(surname),
      name(name),
      patronymic(patronymic),
      institute(institute),
      department(department),
      course(course),
      group(group),
      recordBook(recordBook) {}

Student::Student(int id, const std::string& surname, const std::string& name, const std::string& patronymic,
                 const std::string& institute, const std::string& department, int course, const std::string& group,
                 const std::string& recordBook)
    : id(id),
      surname(surname),
      name(name),
      patronymic(patronymic),
      institute(institute),
      department(department),
      course(course),
      group(group),
      recordBook(recordBook) {}

int Student::getId() const {
    return id;
}

std::string Student::getSurname() const {
    return surname;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getPatronymic() const {
    return patronymic;
}

std::string Student::getInstitute() const {
    return institute;
}

std::string Student::getDepartment() const {
    return department;
}

int Student::getCourse() const {
    return course;
}

std::string Student::getGroup() const {
    return group;
}

std::string Student::getRecordBook() const {
    return recordBook;
}

std::string Student::getFullName() const {
    return surname + " " + name + " " + patronymic;
}

}  // namespace student