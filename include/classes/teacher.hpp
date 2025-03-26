/**
 * @file teacher.hpp
 * @brief Заголовочный файл класса Teacher, представляющего преподавателя
 */

#pragma once

#include <string>

namespace teacher {

/**
 * @class Teacher
 * @brief Класс, описывающий преподавателя университета
 *
 * Содержит информацию:
 * - Персональные данные
 * - Место работы
 * - Уникальный идентификатор
 */
class Teacher {
 private:
  int id;                  ///< Уникальный идентификатор
  std::string surname;     ///< Фамилия
  std::string name;        ///< Имя
  std::string patronymic;  ///< Отчество
  std::string institute;   ///< Институт/факультет
  std::string department;  ///< Кафедра

 public:
  /**
   * @brief Конструктор преподавателя
   * @param id Уникальный идентификатор
   * @param surname Фамилия
   * @param name Имя
   * @param patronymic Отчество
   * @param institute Институт
   * @param department Кафедра
   */
  Teacher(int id, const std::string& surname, const std::string& name,
          const std::string& patronymic, const std::string& institute,
          const std::string& department)
      : id(id),
        surname(surname),
        name(name),
        patronymic(patronymic),
        institute(institute),
        department(department) {}

  /// @brief Деструктор по умолчанию
  ~Teacher() = default;

  /// @name Геттеры
  /// @{
  inline int getId() const { return id; }
  inline std::string getSurname() const { return surname; }
  inline std::string getName() const { return name; }
  inline std::string getPatronymic() const { return patronymic; }
  inline std::string getInstitute() const { return institute; }
  inline std::string getDepartment() const { return department; }
  /// @}

  /**
   * @brief Получить полное имя
   * @return Строка формата "Фамилия Имя Отчество"
   */
  inline std::string getFullName() const {
    return surname + " " + name + " " + patronymic;
  }

};  // class Teacher

}  // namespace teacher