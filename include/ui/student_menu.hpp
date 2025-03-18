#pragma once

#include "../database/database.hpp"
#include "colors.hpp"

namespace menu {

class StudentMenu {
private:
    database::Database& db;
    int studentId;
    
    void printHeader(const std::string& title);
    
public:
    StudentMenu(database::Database& database, int sid);

    ~StudentMenu() = default;

    void show();
    
    void rateCourse();

    void viewRatings();

}; // class StudentMenu

} // namespace menu