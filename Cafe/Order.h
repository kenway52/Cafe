#pragma once

#include "Order.h"
#include "MenuManager.h" // Для доступа к меню
#include "TableManager.h" // Для управления столами
#include <vector>
#include <string>
#include <fstream>
#include <numeric> // Для std::iota

class OrderManager {
private:
    std::vector<Order> orders;
    MenuManager& menuManager; // Ссылка на менеджер меню
    TableManager& tableManager; // Ссылка на менеджер столов
    int nextOrderId;
    const std::string FILENAME = "orders.txt";

    void saveOrders();
    void loadOrders();
    void updateNextOrderId(); // Обновляет nextOrderId на основе загруженных заказов

public:
    OrderManager(MenuManager& menuMgr, TableManager& tableMgr); // Конструктор принимает ссылки

    void createOrder();
    void cancelOrder();
    void displayOrders() const;
    void displayCompletedOrders() const;

    // Вспомогательный метод для других менеджеров
    Order* getOrderById(int id);
    const std::vector<Order>& getAllOrders() const; // Для финансового модуля
};
