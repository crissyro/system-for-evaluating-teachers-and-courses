#pragma once

#include <string>

namespace course {

class Course {
private:
    int id;
    std::string name;
    std::string institute;
    
public:
    Course(int id, const std::string& name, const std::string& institute)
        : id(id), name(name), institute(institute) {}
        
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getInstitute() const { return institute; }
    
}; // Course

} // namespace course