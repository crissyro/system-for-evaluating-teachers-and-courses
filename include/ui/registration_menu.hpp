/**
 * @file registration_menu.hpp
 * @brief Меню регистрации новых студентов
 */

 #pragma once

 #include "../database/database.hpp"
 #include "colors.hpp"
 
 namespace menu {
 
 /**
  * @class RegistrationMenu
  * @brief Регистрирует новых студентов в системе
  */
 class RegistrationMenu {
  private:
   database::Database& db; ///< Ссылка на базу данных
 
  public:
   /**
    * @brief Конструктор, инициализирующий подключение к БД
    * @param database Ссылка на объект базы данных
    */
   explicit RegistrationMenu(database::Database& database);
 
   /// @brief Деструктор по умолчанию
   ~RegistrationMenu() = default;
 
   /**
    * @brief Процесс регистрации студента
    * @return ID нового студента или -1 при ошибке
    */
   int registerStudent();
 
 };  // class RegistrationMenu
 
 }  // namespace menu