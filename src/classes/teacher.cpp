#include "../../include/classes/teacher.hpp"

namespace teacher {

Teacher::Teacher(int id, const std::string& surname, const std::string& name, const std::string& patronymic,
                 const std::string& institute, const std::string& department)
    : id(id), surname(surname), name(name), patronymic(patronymic), institute(institute), department(department) {}

int Teacher::getId() const {
    return id;
}

std::string Teacher::getSurname() const {
    return surname;
}

std::string Teacher::getName() const {
    return name;
}

std::string Teacher::getPatronymic() const {
    return patronymic;
}

std::string Teacher::getInstitute() const {
    return institute;
}

std::string Teacher::getDepartment() const {
    return department;
}

std::string Teacher::getFullName() const {
    return surname + " " + name + " " + patronymic;
}

}  // namespace teacher