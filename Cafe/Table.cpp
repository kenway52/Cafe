#include "Table.h"

Table::Table(int number) : number(number), occupied(false), currentOrderId(-1) {}

int Table::getNumber() const {
    return number;
}

bool Table::isOccupied() const {
    return occupied;
}

int Table::getCurrentOrderId() const {
    return currentOrderId;
}

void Table::occupy(int orderId) {
    occupied = true;
    currentOrderId = orderId;
    std::cout << "Стол " << number << " занят заказом #" << orderId << std::endl;
}

void Table::free() {
    if (occupied) {
        occupied = false;
        currentOrderId = -1;
        std::cout << "Стол " << number << " освобожден." << std::endl;
    } else {
        std::cout << "Стол " << number << " уже свободен." << std::endl;
    }
}

void Table::display() const {
    std::cout << "Стол " << number << ": " << (occupied ? "Занят" : "Свободен");
    if (occupied) {
        std::cout << " (Заказ #" << currentOrderId << ")";
    }
    std::cout << std::endl;
}
