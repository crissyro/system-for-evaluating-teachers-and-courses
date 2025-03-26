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
          const std::string& recordBook)
      : id(0),
        surname(surname),
        name(name),
        patronymic(patronymic),
        institute(institute),
        department(department),
        course(course),
        group(group),
        recordBook(recordBook) {}

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
          const std::string& recordBook)
      : id(id),
        surname(surname),
        name(name),
        patronymic(patronymic),
        institute(institute),
        department(department),
        course(course),
        group(group),
        recordBook(recordBook) {}

  /// @brief Деструктор по умолчанию
  ~Student() = default;

  /// @name Геттеры
  /// @{
  inline int getId() const { return id; }
  inline std::string getSurname() const { return surname; }
  inline std::string getName() const { return name; }
  inline std::string getPatronymic() const { return patronymic; }
  inline std::string getInstitute() const { return institute; }
  inline std::string getDepartment() const { return department; }
  inline int getCourse() const { return course; }
  inline std::string getGroup() const { return group; }
  inline std::string getRecordBook() const { return recordBook; }
  /// @}

  /**
   * @brief Получить полное имя
   * @return Строка формата "Фамилия Имя Отчество"
   */
  inline std::string getFullName() const {
    return surname + " " + name + " " + patronymic;
  }

};  // class Student

}  // namespace student