/**
 * @file teacher_db.hpp
 * @brief Работа с преподавателями в базе данных
 */

#pragma once

#include <vector>

#include "../classes/teacher.hpp"
#include "database.hpp"

namespace database {

/**
 * @class TeacherDB
 * @brief Управление преподавателями в БД
 */
class TeacherDB {
 private:
  sqlite3* db;  ///< Указатель на соединение с БД

 public:
  /**
   * @brief Конструктор, инициализирующий соединение
   * @param database Экземпляр базы данных
   */
  explicit TeacherDB(const Database& database);

  /// @brief Деструктор по умолчанию
  ~TeacherDB() = default;

  /**
   * @brief Добавить преподавателя
   * @param teacher Объект преподавателя
   * @return ID созданной записи
   */
  int addTeacher(const teacher::Teacher& teacher);

  /**
   * @brief Проверить существование преподавателя
   * @param teacherId ID преподавателя
   * @return true если преподаватель существует
   */
  bool exists(int teacherId);

  /**
   * @brief Получить всех преподавателей
   * @return Вектор объектов Teacher
   */
  std::vector<teacher::Teacher> getAllTeachers();

  /**
   * @brief Получить преподавателя по ID
   * @param id Идентификатор преподавателя
   * @return Объект преподавателя
   * @throws std::runtime_error если не найден
   */
  teacher::Teacher getTeacher(int id);

};  // class TeacherDB

}  // namespace database