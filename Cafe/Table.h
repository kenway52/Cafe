#pragma once

#include <iostream>

class Table {
private:
    int number;
    bool occupied;
    int currentOrderId; // -1 если нет заказа, иначе ID заказа

public:
    Table(int number);

    // Геттеры
    int getNumber() const;
    bool isOccupied() const;
    int getCurrentOrderId() const;

    // Методы
    void occupy(int orderId);
    void free();
    void display() const;
};
