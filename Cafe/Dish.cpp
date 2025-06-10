#include "Dish.h"

Dish::Dish(std::string name, double price, std::string category, bool available)
    : name(std::move(name)), price(price), category(std::move(category)), available(available) {}

std::string Dish::getName() const {
    return name;
}

double Dish::getPrice() const {
    return price;
}

std::string Dish::getCategory() const {
    return category;
}

bool Dish::isAvailable() const {
    return available;
}

void Dish::setName(const std::string& name) {
    this->name = name;
}

void Dish::setPrice(double price) {
    this->price = price;
}

void Dish::setCategory(const std::string& category) {
    this->category = category;
}

void Dish::setAvailability(bool available) {
    this->available = available;
}

void Dish::display() const {
    std::cout << "  - " << name << " (" << category << ") - " << price << " руб. "
              << (available ? "[В наличии]" : "[Нет в наличии]") << std::endl;
}
