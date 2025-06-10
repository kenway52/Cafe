#pragma once

#include "MenuManager.h"
#include "OrderManager.h"
#include "TableManager.h"
#include "FinancialManager.h"

class CafeSimulator {
private:
    MenuManager menuManager;
    TableManager tableManager;
    OrderManager orderManager; // Должен быть инициализирован после menuManager и tableManager
    FinancialManager financialManager; // Должен быть инициализирован после orderManager

public:
    CafeSimulator(); // Конструктор, инициализирующий менеджеры

    void run(); // Главный цикл приложения

private:
    void displayMainMenu();
    void handleMenuActions();
    void handleOrderActions();
    void handleTableActions();
    void handleFinancialActions();
};
