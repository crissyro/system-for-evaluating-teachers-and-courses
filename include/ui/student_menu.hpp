/**
 * @file student_menu.hpp
 * @brief Меню студента
 */

 #pragma once

 #include "../database/database.hpp"
 #include "colors.hpp"
 
 namespace menu {
 
 /**
  * @class StudentMenu
  * @brief Функционал доступный студенту
  * 
  * Включает:
  * - Оценку курсов и преподавателей
  * - Просмотр своих оценок
  */
 class StudentMenu {
  private:
   database::Database& db; ///< Ссылка на базу данных
   int studentId;          ///< ID текущего студента
 
   /**
    * @brief Печатает заголовок раздела
    * @param title Текст заголовка
    */
   void printHeader(const std::string& title);
 
  public:
   /**
    * @brief Конструктор, инициализирующий сессию студента
    * @param database Ссылка на БД
    * @param sid ID студента
    */
   StudentMenu(database::Database& database, int sid);
 
   /// @brief Деструктор по умолчанию
   ~StudentMenu() = default;
 
   /**
    * @brief Главный цикл меню студента
    */
   void show();
 
   /**
    * @brief Оценить курс
    */
   void rateCourse();
 
   /**
    * @brief Оценить преподавателя
    */
   void rateTeacher();
 
   /**
    * @brief Просмотр своих оценок
    */
   void viewRatings();
 
 };  // class StudentMenu
 
 }  // namespace menu