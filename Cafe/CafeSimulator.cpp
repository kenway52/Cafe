#include "CafeSimulator.h"
#include "Utils.h" // Для getValidInput, clearScreen, pressEnterToContinue

CafeSimulator::CafeSimulator()
    : menuManager(), // Инициализация MenuManager
      tableManager(), // Инициализация TableManager
      orderManager(menuManager, tableManager), // Инициализация OrderManager с передачей зависимостей
      financialManager(orderManager) // Инициализация FinancialManager с передачей зависимостей
{
    // Менеджеры инициализируются в списке инициализации в порядке объявления.
    // Важно, чтобы зависимости (например, MenuManager для OrderManager) были инициализированы раньше.
}

void CafeSimulator::run() {
    Utils::clearScreen();
    std::cout << "Добро пожаловать в симулятор кафе!" << std::endl;
    Utils::pressEnterToContinue();

    int choice;
    do {
        displayMainMenu();
        choice = Utils::getValidInput<int>("Ваш выбор: ");
        Utils::clearScreen();

        switch (choice) {
            case 1:
                handleMenuActions();
                break;
            case 2:
                handleOrderActions();
                break;
            case 3:
                handleTableActions();
                break;
            case 4:
                handleFinancialActions();
                break;
            case 5:
                std::cout << "Спасибо за использование симулятора кафе. До свидания!\n";
                break;
            default:
                std::cout << "Некорректный выбор. Пожалуйста, попробуйте еще раз.\n";
                Utils::pressEnterToContinue();
                break;
        }
    } while (choice != 5);
}

void CafeSimulator::displayMainMenu() {
    Utils::clearScreen();
    std::cout << "Добро пожаловать в симулятор кафе!\n";
    std::cout << "1. Управление меню\n";
    std::cout << "2. Работа с заказами\n";
    std::cout << "3. Управление столами\n";
    std::cout << "4. Финансовый отчёт\n";
    std::cout << "5. Выход\n";
}

void CafeSimulator::handleMenuActions() {
    int choice;
    do {
        Utils::clearScreen();
        std::cout << "--- Управление меню ---\n";
        std::cout << "1. Добавить блюдо\n";
        std::cout << "2. Редактировать блюдо\n";
        std::cout << "3. Удалить блюдо\n";
        std::cout << "4. Показать меню\n";
        std::cout << "5. Назад в главное меню\n";
        choice = Utils::getValidInput<int>("Ваш выбор: ");

        switch (choice) {
            case 1: menuManager.addDish(); break;
            case 2: menuManager.editDish(); break;
            case 3: menuManager.deleteDish(); break;
            case 4: menuManager.displayMenu(); Utils::pressEnterToContinue(); break;
            case 5: break;
            default: std::cout << "Некорректный выбор.\n"; Utils::pressEnterToContinue(); break;
        }
    } while (choice != 5);
}

void CafeSimulator::handleOrderActions() {
    int choice;
    do {
        Utils::clearScreen();
        std::cout << "--- Работа с заказами ---\n";
        std::cout << "1. Создать новый заказ\n";
        std::cout << "2. Отменить заказ\n";
        std::cout << "3. Показать все заказы\n";
        std::cout << "4. Показать завершенные заказы\n";
        std::cout << "5. Назад в главное меню\n";
        choice = Utils::getValidInput<int>("Ваш выбор: ");

        switch (choice) {
            case 1: orderManager.createOrder(); break;
            case 2: orderManager.cancelOrder(); break;
            case 3: orderManager.displayOrders(); Utils::pressEnterToContinue(); break;
            case 4: orderManager.displayCompletedOrders(); Utils::pressEnterToContinue(); break;
            case 5: break;
            default: std::cout << "Некорректный выбор.\n"; Utils::pressEnterToContinue(); break;
        }
    } while (choice != 5);
}

void CafeSimulator::handleTableActions() {
    int choice;
    do {
        Utils::clearScreen();
        std::cout << "--- Управление столами ---\n";
        std::cout << "1. Показать статус столов\n";
        // В рамках этого симулятора, occupyTable и freeTable вызываются из OrderManager
        // но можно добавить пункты меню для ручного управления столами, если нужно.
        // Сейчас ручное управление не нужно, так как оно привязано к заказам.
        std::cout << "2. Назад в главное меню\n";
        choice = Utils::getValidInput<int>("Ваш выбор: ");

        switch (choice) {
            case 1: tableManager.listTables(); Utils::pressEnterToContinue(); break;
            case 2: break;
            default: std::cout << "Некорректный выбор.\n"; Utils::pressEnterToContinue(); break;
        }
    } while (choice != 2);
}

void CafeSimulator::handleFinancialActions() {
    int choice;
    do {
        Utils::clearScreen();
        std::cout << "--- Финансовый отчёт ---\n";
        std::cout << "1. Учесть прибыль за день\n";
        std::cout << "2. Показать сводку продаж\n";
        std::cout << "3. Сгенерировать текстовый отчёт (report.txt)\n";
        std::cout << "4. Назад в главное меню\n";
        choice = Utils::getValidInput<int>("Ваш выбор: ");

        switch (choice) {
            case 1: financialManager.recordDailyProfit(); break;
            case 2: financialManager.generateSummary(); break;
            case 3: financialManager.generateReport(); break;
            case 4: break;
            default: std::cout << "Некорректный выбор.\n"; Utils::pressEnterToContinue(); break;
        }
    } while (choice != 4);
}
