/**
 * @file database.hpp
 * @brief Базовый класс работы с SQLite
 */

#pragma once

#include <sqlite3.h>

#include <memory>
#include <stdexcept>
#include <string>

namespace database {

/**
 * @class Database
 * @brief Обертка для работы с SQLite
 *
 * Обеспечивает:
 * - Управление соединением
 * - Выполнение запросов
 * - Транзакции
 */
class Database {
 private:
  sqlite3* db;                 ///< Указатель на БД
  static const char* DB_NAME;  ///< Имя файла БД

 public:
  /// @brief Конструктор, открывающий соединение
  Database();

  /// @brief Деструктор, закрывающий соединение
  ~Database();

  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;
  Database(Database&&) = delete;
  Database& operator=(Database&&) = delete;

  /**
   * @class Statement
   * @brief Подготовленный SQL-запрос
   */
  class Statement {
    sqlite3_stmt* stmt;  ///< Указатель на подготовленный запрос

   public:
    /**
     * @brief Конструктор с подготовкой запроса
     * @param db Указатель на БД
     * @param sql SQL-запрос
     */
    Statement(sqlite3* db, const char* sql);

    /// @brief Деструктор с финализацией запроса
    ~Statement();

    /// @brief Неявное преобразование к sqlite3_stmt*
    operator sqlite3_stmt*() const { return stmt; }

    /**
     * @brief Привязать строковое значение
     * @param idx Номер параметра (1-based)
     * @param value Значение для привязки
     */
    void bind(int idx, const std::string& value);

    /**
     * @brief Привязать целочисленное значение
     * @param idx Номер параметра (1-based)
     * @param value Значение для привязки
     */
    void bind(int idx, int value);

  };  // class Statement

  /**
   * @class Transaction
   * @brief Управление транзакциями
   */
  class Transaction {
    sqlite3* db;  ///< Указатель на БД

   public:
    /// @brief Начать транзакцию
    explicit Transaction(sqlite3* db);

    /// @brief Откат при разрушении
    ~Transaction();

    /// @brief Подтвердить транзакцию
    void commit();

    /// @brief Откатить транзакцию
    void rollback();

  };  // class Transaction

  static Database& getInstance();

  /**
   * @brief Получить низкоуровневый дескриптор БД
   * @return Указатель на sqlite3
   */
  sqlite3* getHandle() const { return db; }

  /**
   * @brief Начать новую транзакцию
   * @return unique_ptr управляемого объекта транзакции
   */
  std::unique_ptr<Transaction> beginTransaction();

};  // class Database

}  // namespace database