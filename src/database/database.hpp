#pragma once

#include <sqlite3.h>
#include <memory>
#include <stdexcept>

namespace database {

class Database {
    sqlite3* db;
    static const char* DB_NAME;
    
public:
    Database() {
        if(sqlite3_open(DB_NAME, &db) != SQLITE_OK) { 
            throw std::runtime_error(sqlite3_errmsg(db)); 
        }
    }
    
    ~Database() { sqlite3_close(db); }
    
    class Statement {
    private:
        sqlite3_stmt* stmt;

    public:
        Statement(sqlite3* db, const char* sql) {
            if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                throw std::runtime_error(sqlite3_errmsg(db));
            }
        }
        
        ~Statement() { sqlite3_finalize(stmt); }
        
        operator sqlite3_stmt*() const { return stmt; }
        
        void bind(int idx, const std::string& value) {
            sqlite3_bind_text(stmt, idx, value.c_str(), -1, SQLITE_TRANSIENT);
        }
        
        void bind(int idx, int value) {
            sqlite3_bind_int(stmt, idx, value);
        }
    };
    
    sqlite3* getHandle() const { return db; }
    
    void execute(const char* sql) {
        char* errMsg = nullptr;
        if(sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::string error = errMsg;
            sqlite3_free(errMsg);
            throw std::runtime_error(error);
        }
    }
};

const char* Database::DB_NAME = "university.db";

} // namespace database