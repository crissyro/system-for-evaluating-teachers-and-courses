/**
 * @file course.hpp
 * @brief Заголовочный файл класса Course, представляющего учебный курс
 */

#pragma once

#include <string>

namespace course {

/**
 * @class Course
 * @brief Класс, описывающий учебный курс университета
 *
 * Хранит базовую информацию о курсе:
 * - Уникальный идентификатор
 * - Название курса
 * - Институт, к которому относится курс
 */
class Course {
 private:
  int id;  ///< Уникальный идентификатор курса
  std::string name;       ///< Название курса
  std::string institute;  ///< Институт, предлагающий курс

 public:
  /**
   * @brief Конструктор курса
   * @param id Числовой идентификатор курса (должен быть > 0)
   * @param name Название курса (непустая строка)
   * @param institute Название института (непустая строка)
   */
  Course(int id, const std::string& name, const std::string& institute)
      : id(id), name(name), institute(institute) {}

  /// @brief Виртуальный деструктор по умолчанию
  ~Course() = default;

  /**
   * @brief Получить идентификатор курса
   * @return Целочисленный уникальный идентификатор
   */
  inline int getId() const { return id; }

  /**
   * @brief Получить название курса
   * @return Константная ссылка на строку с названием
   */
  inline const std::string& getName() const { return name; }

  /**
   * @brief Получить название института
   * @return Константная ссылка на строку с институтом
   */
  inline const std::string& getInstitute() const { return institute; }

};  // class Course

}  // namespace course