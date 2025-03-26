/**
 * @file course.hpp
 * @brief Заголовочный файл класса учебного курса
 */

 #pragma once

 #include <string>
 
 namespace course {
 
 /**
  * @class Course
  * @brief Класс, описывающий учебный курс
  * 
  * Данный класс хранит информацию об учебном курсе, включая его идентификатор, 
  * название и институт, к которому он относится.
  */
 class Course {
 private:
     int id;             ///< Уникальный идентификатор курса
     std::string name;   ///< Название курса
     std::string institute; ///< Институт, предлагающий курс
     
 public:
     /**
      * @brief Конструктор курса
      * @param id Идентификатор курса (должен быть положительным)
      * @param name Название курса (не может быть пустой строкой)
      * @param institute Название института (не может быть пустой строкой)
      * @throw std::invalid_argument Если переданы некорректные параметры
      */
     Course(int id, const std::string& name, const std::string& institute);
 
     /// @brief Виртуальный деструктор по умолчанию
     ~Course() = default;
 
     /**
      * @brief Получить ID курса
      * @return Целочисленный идентификатор курса
      */
     inline int getId() const { return id; }
 
     /**
      * @brief Получить название курса
      * @return Константная ссылка на строку с названием курса
      */
     inline const std::string& getName() const { return name; }
 
     /**
      * @brief Получить название института
      * @return Константная ссылка на строку с названием института
      */
     inline const std::string& getInstitute() const { return institute; }
 };
 
 } // namespace course