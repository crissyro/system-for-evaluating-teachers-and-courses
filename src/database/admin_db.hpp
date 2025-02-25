#pragma once

#include "database.hpp"

namespace database {

class AdminDB {
    sqlite3* db;
    
public:
    explicit AdminDB(const Database& database) : db(database.getHandle()) {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS admins (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            );
        )";
        
        Database::Statement stmt(db, sql);
        sqlite3_step(stmt);
    }

    bool addAdmin(const std::string& username, const std::string& password) {
        const char* sql = "INSERT INTO admins (username, password) VALUES (?, ?);";

        Database::Statement stmt(db, sql);
        stmt.bind(1, username);
        stmt.bind(2, password);

        return sqlite3_step(stmt) == SQLITE_DONE;
    }

    bool adminExists(const std::string& username) {
        const char* sql = "SELECT 1 FROM admins WHERE username = ?;";

        Database::Statement stmt(db, sql);
        stmt.bind(1, username);

        return sqlite3_step(stmt) == SQLITE_ROW;
    }
};

} // namespace database