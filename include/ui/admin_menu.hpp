/**
 * @file admin_menu.hpp
 * @brief Меню администратора системы рейтингов
 */

 #pragma once

 #include "../database/database.hpp"
 #include "colors.hpp"
 
 namespace menu {
 
 /**
  * @class AdminMenu
  * @brief Предоставляет функционал для администратора
  * 
  * Включает:
  * - Просмотр всех оценок
  * - Статистику
  * - Управление курсами и преподавателями
  */
 class AdminMenu {
  private:
   database::Database& db; ///< Ссылка на базу данных
 
  public:
   /**
    * @brief Конструктор, инициализирующий подключение к БД
    * @param database Ссылка на объект базы данных
    */
   explicit AdminMenu(database::Database& database);
 
   /// @brief Деструктор по умолчанию
   ~AdminMenu() = default;
 
   /**
    * @brief Главный цикл меню администратора
    */
   void show();
 
   /**
    * @brief Отобразить все оценки системы
    */
   void showAllRatings();
 
   /**
    * @brief Показать статистику оценок
    */
   void showStatistics();
 
   /**
    * @brief Добавить новый курс в систему
    */
   void addCourse();
 
   /**
    * @brief Добавить нового преподавателя
    */
   void addTeacher();
 
 };  // class AdminMenu
 
 }  // namespace menu