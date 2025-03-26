/**
 * @file course_db.hpp
 * @brief Работа с курсами в базе данных
 */

#pragma once

#include <vector>

#include "../classes/course.hpp"
#include "database.hpp"

namespace database {

/**
 * @class CourseDB
 * @brief Управление курсами в БД
 *
 * Реализует CRUD-операции для учебных курсов
 */
class CourseDB {
 private:
  sqlite3* db;  ///< Указатель на соединение с БД

 public:
  /**
   * @brief Конструктор, инициализирующий соединение
   * @param database Экземпляр базы данных
   */
  explicit CourseDB(const Database& database);

  /// @brief Деструктор по умолчанию
  ~CourseDB() = default;

  /**
   * @brief Добавить новый курс
   * @param course Объект курса для добавления
   * @return ID созданной записи
   */
  int addCourse(const course::Course& course);

  /**
   * @brief Получить курс по ID
   * @param id Идентификатор курса
   * @return Объект курса
   * @throws std::runtime_error если курс не найден
   */
  course::Course getCourse(int id);

  /**
   * @brief Проверить существование курса
   * @param courseId Идентификатор курса
   * @return true если курс существует
   */
  bool exists(int courseId);

  /**
   * @brief Получить все курсы
   * @return Вектор объектов курсов
   */
  std::vector<course::Course> getAllCourses();

};  // class CourseDB

}  // namespace database