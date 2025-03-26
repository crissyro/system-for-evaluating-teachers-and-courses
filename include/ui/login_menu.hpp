/**
 * @file login_menu.hpp
 * @brief Меню авторизации пользователей
 */

 #pragma once

 #include "../database/admin_db.hpp"
 #include "../database/database.hpp"
 #include "../database/student_db.hpp"
 #include "colors.hpp"
 
 namespace menu {
 
 /**
  * @class LoginMenu
  * @brief Обрабатывает вход студентов и администраторов
  */
 class LoginMenu {
  private:
   database::Database& db; ///< Ссылка на базу данных
 
  public:
   /**
    * @brief Конструктор, инициализирующий подключение к БД
    * @param database Ссылка на объект базы данных
    */
   LoginMenu(database::Database& database);
 
   /// @brief Деструктор по умолчанию
   ~LoginMenu() = default;
 
   /**
    * @brief Авторизация студента
    * @return ID студента или -1 при ошибке
    */
   int loginStudent();
 
   /**
    * @brief Авторизация администратора
    * @return true при успешной аутентификации
    */
   bool loginAdmin();
 };
 
 }  // namespace menu