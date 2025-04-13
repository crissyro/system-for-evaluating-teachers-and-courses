#include "../../include/classes/course.hpp"

namespace course {

Course::Course(int id, const std::string& name, const std::string& institute)
    : id(id), name(name), institute(institute) {}

int Course::getId() const {
    return id;
}

const std::string& Course::getName() const {
    return name;
}

const std::string& Course::getInstitute() const {
    return institute;
}

}  // namespace course