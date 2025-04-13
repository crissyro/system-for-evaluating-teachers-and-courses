#include "../../include/classes/student.hpp"

namespace student {

Student::Student(const std::string& surname, const std::string& name,
        const std::string& patronymic, const std::string& institute,
        const std::string& department, int course, const std::string& group,
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


Student::Student(int id, const std::string& surname, const std::string& name,
        const std::string& patronymic, const std::string& institute,
        const std::string& department, int course, const std::string& group,
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



inline int Student::getId() const { 
    return id; 
}

inline std::string Student::getSurname() const { 
    return surname; 
}

inline std::string Student::getName() const { 
    return name; 
}

inline std::string Student::getPatronymic() const { 
    return patronymic; 
}

inline std::string Student::getInstitute() const { 
    return institute; 
}

inline std::string Student::getDepartment() const { 
    return department; 
}

inline int Student::getCourse() const { 
    return course; 
}

inline std::string Student::getGroup() const { 
    return group; 
}

inline std::string Student::getRecordBook() const { 
    return recordBook; 
}

inline std::string Student::getFullName() const {
  return surname + " " + name + " " + patronymic;
}

}