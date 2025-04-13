/**
 * @file student.hpp
 * @brief Заголовочный файл класса Student, представляющего студента
 */

#pragma once

#include <string>

namespace student {

/**
 * @class Student
 * @brief Класс, описывающий студента университета
 *
 * Содержит полную информацию о студенте:
 * - Персональные данные
 * - Учебные характеристики
 * - Уникальные идентификаторы
 */
class Student {
 private:
  int id;                  ///< Уникальный идентификатор
  std::string surname;     ///< Фамилия студента
  std::string name;        ///< Имя студента
  std::string patronymic;  ///< Отчество студента
  std::string institute;   ///< Институт/факультет
  std::string department;  ///< Кафедра
  int course;              ///< Курс обучения
  std::string group;       ///< Учебная группа
  std::string recordBook;  ///< Номер зачетной книжки

 public:
  /**
   * @brief Конструктор для нового студента (без ID)
   * @param surname Фамилия
   * @param name Имя
   * @param patronymic Отчество
   * @param institute Институт
   * @param department Кафедра
   * @param course Курс
   * @param group Группа
   * @param recordBook Номер зачетки
   */
  Student(const std::string& surname, const std::string& name,
          const std::string& patronymic, const std::string& institute,
          const std::string& department, int course, const std::string& group,
          const std::string& recordBook);

  /**
   * @brief Конструктор для существующего студента (с ID)
   * @param id Уникальный идентификатор
   * @param surname Фамилия
   * @param name Имя
   * @param patronymic Отчество
   * @param institute Институт
   * @param department Кафедра
   * @param course Курс
   * @param group Группа
   * @param recordBook Номер зачетки
   */
  Student(int id, const std::string& surname, const std::string& name,
          const std::string& patronymic, const std::string& institute,
          const std::string& department, int course, const std::string& group,
          const std::string& recordBook);

  /// @brief Деструктор по умолчанию
  ~Student() = default;

  /// @name Геттеры
  /// @{
  inline int getId() const;
  inline std::string getSurname() const;
  inline std::string getName() const;
  inline std::string getPatronymic() const;
  inline std::string getInstitute() const;
  inline std::string getDepartment() const;
  inline int getCourse() const;
  inline std::string getGroup() const;
  inline std::string getRecordBook() const;
  /// @}

  /**
   * @brief Получить полное имя
   * @return Строка формата "Фамилия Имя Отчество"
   */
  inline std::string getFullName() const;

};  // class Student

}  // namespace student