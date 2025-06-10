#include "TableManager.h"
#include "Utils.h"

TableManager::TableManager() {
    tables.reserve(NUM_TABLES); // Резервируем память
    for (int i = 1; i <= NUM_TABLES; ++i) {
        tables.emplace_back(i); // Создаем столы с номерами 1 до NUM_TABLES
    }
}

void TableManager::listTables() const {
    std::cout << "\n--- Статус столов ---" << std::endl;
    for (const auto& table : tables) {
        table.display();
    }
    std::cout << "---------------------" << std::endl;
}

void TableManager::occupyTable(int tableNumber, int orderId) {
    Table* table = getTableByNumber(tableNumber);
    if (table) {
        if (!table->isOccupied()) {
            table->occupy(orderId);
        } else {
            std::cout << "Ошибка: Стол " << tableNumber << " уже занят." << std::endl;
        }
    } else {
        std::cout << "Ошибка: Стол " << tableNumber << " не существует." << std::endl;
    }
}

void TableManager::freeTable(int tableNumber) {
    Table* table = getTableByNumber(tableNumber);
    if (table) {
        table->free();
    } else {
        std::cout << "Ошибка: Стол " << tableNumber << " не существует." << std::endl;
    }
}

Table* TableManager::getTableByNumber(int number) {
    if (number >= 1 && number <= NUM_TABLES) {
        return &tables[number - 1]; // Столы с 1 до NUM_TABLES, индексы с 0 до NUM_TABLES-1
    }
    return nullptr;
}
