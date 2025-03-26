#pragma once

#include <string>

namespace teacher {
class Teacher {
 private:
  int id;
  std::string surname;
  std::string name;
  std::string patronymic;
  std::string institute;
  std::string department;

 public:
  Teacher(int id, const std::string& surname, const std::string& name,
          const std::string& patronymic, const std::string& institute,
          const std::string& department)
      : id(id),
        surname(surname),
        name(name),
        patronymic(patronymic),
        institute(institute),
        department(department) {}

  ~Teacher() = default;

  inline int getId() const { return id; }

  inline std::string getSurname() const { return surname; }

  inline std::string getName() const { return name; }

  inline std::string getPatronymic() const { return patronymic; }

  inline std::string getInstitute() const { return institute; }

  inline std::string getDepartment() const { return department; }

  inline std::string getFullName() const {
    return surname + " " + name + " " + patronymic;
  }

};  // Teacher

}  // namespace teacher