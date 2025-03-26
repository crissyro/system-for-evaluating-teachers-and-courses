/**
 * @file rating_db.hpp
 * @brief Работа с рейтингами в базе данных
 */

#pragma once

#include <utility>
#include <vector>

#include "../classes/rating.hpp"
#include "database.hpp"

namespace database {

/**
 * @class RatingDB
 * @brief Управление рейтингами курсов и преподавателей
 */
class RatingDB {
 private:
  sqlite3* db;  ///< Указатель на соединение с БД

 public:
  /// @brief Статистика оценок
  struct Statistics {
    std::vector<std::pair<int, double>> courseStats;  ///< Средние оценки курсов
    std::vector<std::pair<int, double>>
        teacherStats;  ///< Средние оценки преподавателей
  };

  /**
   * @brief Конструктор, инициализирующий соединение
   * @param database Экземпляр базы данных
   */
  explicit RatingDB(const Database& database);

  /// @brief Деструктор по умолчанию
  ~RatingDB() = default;

  /**
   * @brief Добавить оценку курсу
   * @param studentId ID студента
   * @param courseId ID курса
   * @param rating Значение оценки (1-5)
   * @return true при успешном добавлении
   */
  bool addCourseRating(int studentId, int courseId, int rating);

  /**
   * @brief Добавить оценку преподавателю
   * @param studentId ID студента
   * @param teacherId ID преподавателя
   * @param rating Значение оценки (1-5)
   * @return true при успешном добавлении
   */
  bool addTeacherRating(int studentId, int teacherId, int rating);

  /**
   * @brief Получить все оценки
   * @return Вектор объектов Rating
   */
  std::vector<rating::Rating> getAllRatings();

  /**
   * @brief Получить статистику оценок
   * @return Структура Statistics с усредненными значениями
   */
  Statistics getStatistics();

  /**
   * @brief Проверить существование оценки
   * @param studentId ID студента
   * @param entityId ID сущности (курса/преподавателя)
   * @param isCourse Тип сущности
   * @return true если оценка уже существует
   */
  bool hasExistingRating(int studentId, int entityId, bool isCourse);

  /// @name Методы получения оценок
  /// @{
  std::vector<std::pair<int, int>> getCourseRatings(int studentId);
  std::vector<std::pair<int, int>> getTeacherRatings(int studentId);
  std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>>
  getStudentRatings(int studentId);
  /// @}

};  // class RatingDB

}  // namespace database