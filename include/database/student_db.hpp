/**
 * @file student_db.hpp
 * @brief Работа со студентами в базе данных
 */

#pragma once

#include "../classes/student.hpp"
#include "database.hpp"

namespace database {

/**
 * @class StudentDB
 * @brief Управление студентами в БД
 */
class StudentDB {
 private:
  sqlite3* db;  ///< Указатель на соединение с БД

 public:
  /**
   * @brief Конструктор, инициализирующий соединение
   * @param database Экземпляр базы данных
   */
  explicit StudentDB(const Database& database);

  /// @brief Деструктор по умолчанию
  ~StudentDB() = default;

  /**
   * @brief Добавить студента
   * @param student Объект студента
   * @return ID созданной записи
   */
  int addStudent(const student::Student& student);

  /**
   * @brief Проверить существование по номеру зачетки
   * @param recordBook Номер зачетной книжки
   * @return true если студент существует
   */
  bool exists(const std::string& recordBook);

  /**
   * @brief Получить ID студента по зачетке
   * @param recordBook Номер зачетной книжки
   * @return ID студента или -1 если не найден
   */
  int getStudentIdByRecordBook(const std::string& recordBook);

};  // class StudentDB

}  // namespace database