
#include "Utils.h"
#include <cstdlib> // Для system("cls") или system("clear")

namespace Utils {
    std::string getStringInput(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    void clearScreen() {
        // Проверка операционной системы для очистки консоли
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void pressEnterToContinue() {
        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера перед следующим getline
        // Для macOS/Linux: std::cin.get();
        // Для Windows: std::cin.get();
        // Но обычно достаточно очистить буфер и просто ждать ввода.
        // Более универсально:
        std::string dummy;
        std::getline(std::cin, dummy); // Просто ждем Enter
    }
}
