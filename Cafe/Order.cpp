
#include "Order.h"
#include <numeric> // Для std::accumulate
#include <sstream> // Для stringstream

Order::Order(int id, int tableNumber) : id(id), totalAmount(0.0), cancelled(false), tableNumber(tableNumber) {
    // Генерация текущего времени
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
    timestamp = ss.str();
}

int Order::getId() const {
    return id;
}

std::string Order::getTimestamp() const {
    return timestamp;
}

const std::vector<Order::OrderItem>& Order::getItems() const {
    return items;
}

double Order::getTotalAmount() const {
    return totalAmount;
}

bool Order::isCancelled() const {
    return cancelled;
}

int Order::getTableNumber() const {
    return tableNumber;
}

void Order::addItem(const std::string& dishName, double pricePerUnit, int quantity) {
    items.push_back({dishName, pricePerUnit, quantity});
    calculateTotal(); // Пересчитываем сумму при добавлении
}

void Order::calculateTotal() {
    totalAmount = 0.0;
    for (const auto& item : items) {
        totalAmount += item.pricePerUnit * item.quantity;
    }
}

void Order::cancel() {
    cancelled = true;
    std::cout << "Заказ #" << id << " отменен." << std::endl;
}

void Order::display() const {
    std::cout << "--- Заказ #" << id << " (Стол " << tableNumber << ") ---" << std::endl;
    std::cout << "Время: " << timestamp << std::endl;
    std::cout << "Статус: " << (cancelled ? "Отменен" : "Активен/Завершен") << std::endl;
    std::cout << "Блюда:" << std::endl;
    for (const auto& item : items) {
        std::cout << "  - " << item.dishName << " x" << item.quantity
                  << " (" << item.pricePerUnit << " руб./шт.)" << std::endl;
    }
    std::cout << "Итого: " << totalAmount << " руб." << std::endl;
    std::cout << "----------------------" << std::endl;
}

std::string Order::serialize() const {
    std::stringstream ss;
    ss << "ORDER_ID:" << id << "\n";
    ss << "TIMESTAMP:" << timestamp << "\n";
    ss << "TOTAL:" << totalAmount << "\n";
    ss << "CANCELLED:" << (cancelled ? "1" : "0") << "\n";
    ss << "TABLE:" << tableNumber << "\n";
    for (const auto& item : items) {
        ss << "DISH_ITEM:" << item.dishName << "," << item.pricePerUnit << "," << item.quantity << "\n";
    }
    return ss.str();
}

Order Order::deserialize(const std::vector<std::string>& lines) {
    int id = 0;
    std::string timestamp;
    double totalAmount = 0.0;
    bool cancelled = false;
    int tableNumber = 0;
    std::vector<OrderItem> items;

    for (const std::string& line : lines) {
        if (line.rfind("ORDER_ID:", 0) == 0) {
            id = std::stoi(line.substr(9));
        } else if (line.rfind("TIMESTAMP:", 0) == 0) {
            timestamp = line.substr(10);
        } else if (line.rfind("TOTAL:", 0) == 0) {
            totalAmount = std::stod(line.substr(6));
        } else if (line.rfind("CANCELLED:", 0) == 0) {
            cancelled = (line.substr(10) == "1");
        } else if (line.rfind("TABLE:", 0) == 0) {
            tableNumber = std::stoi(line.substr(6));
        } else if (line.rfind("DISH_ITEM:", 0) == 0) {
            std::string itemData = line.substr(10);
            std::stringstream ss(itemData);
            std::string dishName;
            std::string priceStr;
            std::string quantityStr;

            std::getline(ss, dishName, ',');
            std::getline(ss, priceStr, ',');
            std::getline(ss, quantityStr, ',');

            items.push_back({dishName, std::stod(priceStr), std::stoi(quantityStr)});
        }
    }

    Order order(id, tableNumber);
    order.timestamp = timestamp; // Устанавливаем время из файла
    order.totalAmount = totalAmount; // Устанавливаем сумму из файла
    order.cancelled = cancelled; // Устанавливаем статус отмены
    order.items = items; // Устанавливаем список блюд

    return order;
}
