#include "../../include/classes/teacher.hpp"

namespace teacher {

Teacher::Teacher(int id, const std::string& surname, const std::string& name,
        const std::string& patronymic, const std::string& institute,
        const std::string& department)
    : id(id),
      surname(surname),
      name(name),
      patronymic(patronymic),
      institute(institute),
      department(department) {}


inline int Teacher::getId() const { 
    return id; 
}

inline std::string Teacher::getSurname() const { 
    return surname; 
}

inline std::string Teacher::getName() const { 
    return name; 
}

inline std::string Teacher::getPatronymic() const { 
    return patronymic; 
}

inline std::string Teacher::getInstitute() const { 
    return institute; 
}

inline std::string Teacher::getDepartment() const { 
    return department; 
}

inline std::string Teacher::getFullName() const {
  return surname + " " + name + " " + patronymic;
}

}