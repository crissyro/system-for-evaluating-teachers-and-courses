/**
 * @file colors.hpp
 * @brief ANSI-коды для цветного вывода в консоль
 * 
 * @def RESET Сброс цвета
 * @def RED Красный цвет
 * @def GREEN Зеленый цвет
 * @def YELLOW Желтый цвет
 * @def BLUE Синий цвет
 * @def MAGENTA Пурпурный цвет
 * @def CYAN Голубой цвет
 * @def BOLD Жирный шрифт
 */

 #pragma once

 #define RESET "\033[0m"    ///< Сброс стилей
 #define RED "\033[31m"     ///< Текст красного цвета
 #define GREEN "\033[32m"   ///< Текст зеленого цвета
 #define YELLOW "\033[33m"  ///< Текст желтого цвета
 #define BLUE "\033[34m"    ///< Текст синего цвета
 #define MAGENTA "\033[35m" ///< Текст пурпурного цвета
 #define CYAN "\033[36m"    ///< Текст голубого цвета
 #define BOLD "\033[1m"     ///< Жирное начертание