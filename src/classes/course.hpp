#pragma once 

#include <iostream>

namespace course {

class Course {

private:
    int id;
    std::string name;
    std::string institute;

public:
    Course(int id, const std::string& name, const std::string& institute)
        : id(id), name(name), institute(institute) {}

    inline const int getId() const { return id; }
    inline const std::string& getName() const { return name; }
    inline const std::string& getInstitute() const { return institute; }

    inline void setId(const int id_) { this->id = id_; };
    inline void setName(const std::string& name_) { this->name = name_; };
    inline void setInstitute(const std::string& institute_) { this->institute = institute_; };
};

}; // end namespace course