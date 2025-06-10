#pragma once

#include <string>
#include <iostream>

class Dish {
private:
    std::string name;
    double price;
    std::string category;
    bool available;

public:
    // Конструктор
    Dish(std::string name, double price, std::string category, bool available = true);

    // Геттеры
    std::string getName() const;
    double getPrice() const;
    std::string getCategory() const;
    bool isAvailable() const;

    // Сеттеры
    void setName(const std::string& name);
    void setPrice(double price);
    void setCategory(const std::string& category);
    void setAvailability(bool available);

    // Вывод информации о блюде
    void display() const;
};
