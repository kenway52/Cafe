#pragma once

#include <string>
#include <limits> // Для numeric_limits
#include <iostream>

namespace Utils {
    // Очищает буфер ввода и проверяет корректность введенных данных
    template <typename T>
    T getValidInput(const std::string& prompt) {
        T value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;

            if (std::cin.fail()) {
                std::cout << "Некорректный ввод. Пожалуйста, введите число.\n";
                std::cin.clear(); // Сброс флагов ошибок
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование оставшейся строки
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование оставшейся строки
                return value;
            }
        }
    }

    // Для ввода строк (не требует такой строгой валидации типа, как числа)
    std::string getStringInput(const std::string& prompt);

    // Очищает консоль
    void clearScreen();

    // Пауза, ожидание нажатия Enter
    void pressEnterToContinue();
}
