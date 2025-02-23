#pragma once 

#include <iostream>

namespace teacher {

class Teacher {

private:
    int id;
    std::string fio;
    std::string institute;
    std::string department;

public:

    Teacher(int id, const std::string& fio, const std::string& institute, const std::string& department)
        : id(id), fio(fio), institute(institute), department(department) {}

    inline const int getId() const { return id; }
    inline const std::string& getFio() const { return fio; }
    inline const std::string& getInstitute() const { return institute; }
    inline const std::string& getDepartment() const { return department; }

    inline void setId(const int id_) { this->id = id_; };
    inline void setFio(const std::string& fio_) { this->fio = fio_; };
    inline void setInstitute(const std::string& institute_) { this->institute = institute_; };
    inline void setDepartment(const std::string& department_) { this->department = department_; };
};

}; // end of namespace teacher