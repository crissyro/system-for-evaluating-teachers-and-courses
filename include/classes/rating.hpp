/**
 * @file rating.hpp
 * @brief Заголовочный файл класса Rating, представляющего оценку
 */

#pragma once

namespace rating {

/**
 * @class Rating
 * @brief Класс, хранящий информацию об оценке
 *
 * Может представлять оценку как для курса, так и для преподавателя.
 * Содержит:
 * - ID студента
 * - ID оцениваемой сущности (курса или преподавателя)
 * - Значение оценки
 * - Флаг типа оценки
 */
class Rating {
 private:
  int studentId;  ///< ID студента, поставившего оценку
  int entityId;  ///< ID сущности (курса или преподавателя)
  int value;      ///< Значение оценки (1-5)
  bool isCourse;  ///< Флаг типа оценки (true - курс, false - преподаватель)

 public:
  /**
   * @brief Конструктор оценки
   * @param sid ID студента
   * @param eid ID сущности
   * @param val Значение оценки
   * @param isCourse Флаг типа оценки
   */
  Rating(int sid, int eid, int val, bool isCourse)
      : studentId(sid), entityId(eid), value(val), isCourse(isCourse) {}

  /// @brief Деструктор по умолчанию
  ~Rating() = default;

  /**
   * @brief Получить ID студента
   * @return Целочисленный ID студента
   */
  inline int getStudentId() const { return studentId; }

  /**
   * @brief Получить ID сущности
   * @return Целочисленный ID курса/преподавателя
   */
  inline int getEntityId() const { return entityId; }

  /**
   * @brief Получить значение оценки
   * @return Оценка в диапазоне 1-5
   */
  inline int getValue() const { return value; }

  /**
   * @brief Проверка типа оценки
   * @return true - оценка за курс, false - за преподавателя
   */
  inline bool isCourseRating() const { return isCourse; }

};  // class Rating

}  // namespace rating