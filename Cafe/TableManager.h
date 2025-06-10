#pragma once

#include "Table.h"
#include <vector>
#include <iostream>

class TableManager {
private:
    std::vector<Table> tables;
    const int NUM_TABLES = 5; // Например, 5 столов

public:
    TableManager(); // Конструктор, инициализирующий столы

    void listTables() const;
    void occupyTable(int tableNumber, int orderId); // Сразу привязываем заказ
    void freeTable(int tableNumber);

    // Вспомогательные методы
    Table* getTableByNumber(int number);
};
