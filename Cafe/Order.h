#pragma once

#include <string>
#include <vector>
#include <utility> // Для std::pair
#include <ctime>   // Для timestamp
#include <iomanip> // Для std::put_time

class Order {
public:
    struct OrderItem {
        std::string dishName;
        double pricePerUnit;
        int quantity;
    };

private:
    int id;
    std::string timestamp; // Формат YYYY-MM-DD HH:MM:SS
    std::vector<OrderItem> items;
    double totalAmount;
    bool cancelled;
    int tableNumber;

public:
    Order(int id, int tableNumber);

    // Геттеры
    int getId() const;
    std::string getTimestamp() const;
    const std::vector<OrderItem>& getItems() const;
    double getTotalAmount() const;
    bool isCancelled() const;
    int getTableNumber() const;

    // Методы
    void addItem(const std::string& dishName, double pricePerUnit, int quantity);
    void calculateTotal();
    void cancel();
    void display() const;

    // Для сохранения/загрузки
    std::string serialize() const;
    static Order deserialize(const std::vector<std::string>& lines);
};
