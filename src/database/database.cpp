#include "../../include/database/database.hpp"

namespace database {

const char* Database::DB_NAME = "university.db";

Database::Database() {
    if(sqlite3_open(DB_NAME, &db) != SQLITE_OK) { 
        throw std::runtime_error(sqlite3_errmsg(db)); 
    }

    const char* pragma = "PRAGMA foreign_keys = ON;";
    sqlite3_exec(db, pragma, nullptr, nullptr, nullptr);
}

Database::~Database() { 
    sqlite3_close(db); 
}

Database::Statement::Statement(sqlite3* db, const char* sql) {
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
}

Database::Statement::~Statement() { 
    sqlite3_finalize(stmt); 
}

void Database::Statement::bind(int idx, const std::string& value) {
    sqlite3_bind_text(stmt, idx, value.c_str(), -1, SQLITE_TRANSIENT);
}

void Database::Statement::bind(int idx, int value) {
    sqlite3_bind_int(stmt, idx, value);
}

Database::Transaction::Transaction(sqlite3* db) : db(db) {
    sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
}

Database::Transaction::~Transaction() {
    if(db) rollback();
}

void Database::Transaction::commit() {
    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
    db = nullptr;
}

void Database::Transaction::rollback() {
    sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
    db = nullptr;
}

std::unique_ptr<Database::Transaction> Database::beginTransaction() {
    return std::make_unique<Transaction>(db);
}

} // namespace database