#pragma once

#include <sqlite3.h>
#include <stdexcept>
#include <memory>
#include <string>

namespace database {

class Database {
    sqlite3* db;
    static const char* DB_NAME;
    
public:
    Database();
    ~Database();
    
    class Statement {
        sqlite3_stmt* stmt;
    public:
        Statement(sqlite3* db, const char* sql);
        ~Statement();
        
        operator sqlite3_stmt*() const { return stmt; }
        
        void bind(int idx, const std::string& value);
        void bind(int idx, int value);
    }; // Statement
    
    sqlite3* getHandle() const { return db; }
    
    class Transaction {
        sqlite3* db;
    public:
        explicit Transaction(sqlite3* db);
        ~Transaction();
        void commit();
        void rollback();
    }; // Transaction
    
    std::unique_ptr<Transaction> beginTransaction();

}; //Database

} // namespace database