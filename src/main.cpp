#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <limits>


void setStdinEcho(bool enable = true) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);

    if (!enable) {
        tty.c_lflag &= ~ECHO;
    } else {
        tty.c_lflag |= ECHO;
    }

    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

bool adminLogin() {
    const std::string adminPassword = "admin123"; 
    std::string input;
    
    std::cout << "Введите пароль администратора: ";
    setStdinEcho(false); 

    std::getline(std::cin, input);
    setStdinEcho(true); 

    std::cout << std::endl;

    return input == adminPassword;
}

void studentMenu() {
    std::cout << "\n=== Меню студента ===" << std::endl;
    // Реализация функционала для студента
}

void teacherMenu() {
    std::cout << "\n=== Меню преподавателя ===" << std::endl;
    // Реализация функционала для преподавателя
}

void staffMenu() {
    std::cout << "\n=== Меню сотрудника ===" << std::endl;
    // Реализация функционала для сотрудника
}

void adminMenu() {
    std::cout << "\n=== Административное меню ===" << std::endl;
    // Реализация административных функций
}

void mainMenu() {
    int choice;
    do {
        std::cout << "\nГлавное меню:\n"
                  << "1. Войти как студент\n"
                  << "2. Войти как преподаватель\n"
                  << "3. Войти как сотрудник\n"
                  << "4. Войти как администратор\n"
                  << "0. Выход\n"
                  << "Выберите вариант: ";
             
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                studentMenu();
                break;
            case 2:
                teacherMenu();
                break;
            case 3:
                staffMenu();
                break;
            case 4:
                if (adminLogin()) {
                    adminMenu();
                } else {
                    std::cout << "Ошибка: Неверный пароль!" << std::endl;
                }
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}