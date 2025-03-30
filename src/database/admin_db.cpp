#include "../../include/database/admin_db.hpp"

#include <stdexcept>

namespace database {

AdminDB::AdminDB(const Database& database) : db(database.getHandle()) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS admins (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        );)";

    Database::Statement stmt(db, sql);
    sqlite3_step(stmt);

    if (!adminExists("admin")) {
        const char* insert_sql = "INSERT INTO admins (username, password) VALUES ('admin', 'admin123');";

        Database::Statement insert_stmt(db, insert_sql);
        sqlite3_step(insert_stmt);
    }
}

bool AdminDB::adminExists(const std::string& username) {
    const char* sql = "SELECT 1 FROM admins WHERE username = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, username);

    return sqlite3_step(stmt) == SQLITE_ROW;
}

bool AdminDB::addAdmin(const std::string& username) {
    const char* sql = "INSERT INTO admins (username, password) VALUES (?, ?);";
    Database::Statement stmt(db, sql);
    stmt.bind(1, username);
    stmt.bind(2, "admin123");
    return sqlite3_step(stmt) == SQLITE_DONE;
}

bool AdminDB::checkCredentials(const std::string& username, const std::string& password) {
    const char* sql = "SELECT password FROM admins WHERE username = ?;";

    Database::Statement stmt(db, sql);
    stmt.bind(1, username);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string stored_password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        return password == "admin123";
    }

    return false;
}

}  // namespace database