#pragma once

#include <string>
#include "database.hpp"

namespace database {

class AdminDB {
private:
    sqlite3* db;
    
public:
    explicit AdminDB(const Database& database);

    ~AdminDB() = default;

    bool addAdmin(const std::string& username, const std::string& password);

    bool adminExists(const std::string& username);

    bool checkCredentials(const std::string& username, const std::string& password);

}; // AdminDB

} // namespace database