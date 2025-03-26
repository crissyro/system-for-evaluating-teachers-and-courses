/**
 * @file admin_db.hpp
 * @brief Работа с администраторами в базе данных
 */

#pragma once

#include <string>

#include "database.hpp"

namespace database {

/**
 * @class AdminDB
 * @brief Управление учетными записями администраторов
 *
 * Обеспечивает:
 * - Добавление новых администраторов
 * - Проверку существования пользователя
 * - Аутентификацию
 */
class AdminDB {
 private:
  sqlite3* db;  ///< Указатель на соединение с БД

 public:
  /**
   * @brief Конструктор, инициализирующий соединение
   * @param database Экземпляр базы данных
   */
  explicit AdminDB(const Database& database);

  /// @brief Деструктор по умолчанию
  ~AdminDB() = default;

  /**
   * @brief Добавить администратора
   * @param username Логин администратора
   * @return true если операция успешна
   */
  bool addAdmin(const std::string& username);

  /**
   * @brief Проверить существование администратора
   * @param username Логин для проверки
   * @return true если пользователь существует
   */
  bool adminExists(const std::string& username);

  /**
   * @brief Проверка учетных данных
   * @param username Логин
   * @param password Пароль
   * @return true если аутентификация успешна
   */
  bool checkCredentials(const std::string& username,
                        const std::string& password);

};  // class AdminDB

}  // namespace database