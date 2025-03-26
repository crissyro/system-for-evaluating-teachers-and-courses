/**
 * @file main_menu.hpp
 * @brief Главное меню приложения
 */

 #pragma once

 #include "../database/database.hpp"
 #include "colors.hpp"
 
 namespace menu {
 
 /**
  * @class MainMenu
  * @brief Центральный узел навигации приложения
  * 
  * Обеспечивает переходы:
  * - Вход/регистрация
  * - Меню студента
  * - Меню администратора
  */
 class MainMenu {
  private:
   database::Database& db; ///< Ссылка на базу данных
 
  public:
   /**
    * @brief Конструктор, инициализирующий подключение к БД
    * @param database Ссылка на объект базы данных
    */
   explicit MainMenu(database::Database& database);
 
   /// @brief Деструктор по умолчанию
   ~MainMenu() = default;
 
   /**
    * @brief Главный цикл приложения
    */
   void run();
 
 };  // class MainMenu
 
 }  // namespace menu