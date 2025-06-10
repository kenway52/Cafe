#include "MenuManager.h"
#include "Utils.h" // Для getValidInput, getStringInput
#include <sstream> // Для stringstream

MenuManager::MenuManager() {
    loadMenu();
}

void MenuManager::saveMenu() {
    std::ofstream outFile(FILENAME);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << FILENAME << " для записи." << std::endl;
        return;
    }
    for (const auto& dish : dishes) {
        outFile << dish.getName() << ","
                << dish.getPrice() << ","
                << dish.getCategory() << ","
                << (dish.isAvailable() ? "1" : "0") << "\n";
    }
    outFile.close();
}

void MenuManager::loadMenu() {
    std::ifstream inFile(FILENAME);
    if (!inFile.is_open()) {
        std::cerr << "Информация: Файл меню " << FILENAME << " не найден или пуст. Будет создан новый." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string name, priceStr, category, availableStr;

        if (std::getline(ss, name, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, category, ',') &&
            std::getline(ss, availableStr))
        {
            try {
                double price = std::stod(priceStr);
                bool available = (availableStr == "1");
                dishes.emplace_back(name, price, category, available);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка парсинга строки в меню: " << line << " (" << e.what() << ")" << std::endl;
            }
        }
    }
    inFile.close();
}

void MenuManager::addDish() {
    Utils::clearScreen();
    std::cout << "--- Добавление нового блюда ---" << std::endl;
    std::string name = Utils::getStringInput("Введите название блюда: ");
    double price = Utils::getValidInput<double>("Введите цену блюда: ");
    std::string category = Utils::getStringInput("Введите категорию блюда (например, 'Завтрак', 'Обед', 'Напитки'): ");

    // Проверка на дубликаты
    for (const auto& dish : dishes) {
        if (dish.getName() == name) {
            std::cout << "Блюдо с таким названием уже существует!" << std::endl;
            Utils::pressEnterToContinue();
            return;
        }
    }

    dishes.emplace_back(name, price, category);
    saveMenu();
    std::cout << "Блюдо '" << name << "' успешно добавлено." << std::endl;
    Utils::pressEnterToContinue();
}

void MenuManager::editDish() {
    Utils::clearScreen();
    std::cout << "--- Редактирование блюда ---" << std::endl;
    displayMenu();
    std::string nameToEdit = Utils::getStringInput("Введите название блюда для редактирования: ");

    Dish* dishToEdit = nullptr;
    for (auto& dish : dishes) {
        if (dish.getName() == nameToEdit) {
            dishToEdit = &dish;
            break;
        }
    }

    if (dishToEdit) {
        std::cout << "Найденное блюдо: ";
        dishToEdit->display();
        std::cout << "\nВыберите что редактировать:\n";
        std::cout << "1. Название\n";
        std::cout << "2. Цену\n";
        std::cout << "3. Категорию\n";
        std::cout << "4. Наличие\n";
        int choice = Utils::getValidInput<int>("Ваш выбор: ");

        switch (choice) {
            case 1: {
                std::string newName = Utils::getStringInput("Введите новое название: ");
                // Проверить, не существует ли уже блюдо с таким новым именем
                for (const auto& dish : dishes) {
                    if (dish.getName() == newName && dish.getName() != nameToEdit) {
                        std::cout << "Блюдо с таким названием уже существует!" << std::endl;
                        Utils::pressEnterToContinue();
                        return;
                    }
                }
                dishToEdit->setName(newName);
                break;
            }
            case 2: {
                double newPrice = Utils::getValidInput<double>("Введите новую цену: ");
                dishToEdit->setPrice(newPrice);
                break;
            }
            case 3: {
                std::string newCategory = Utils::getStringInput("Введите новую категорию: ");
                dishToEdit->setCategory(newCategory);
                break;
            }
            case 4: {
                int availChoice = Utils::getValidInput<int>("Установить в наличии (1 - Да, 0 - Нет): ");
                dishToEdit->setAvailability(availChoice == 1);
                break;
            }
            default:
                std::cout << "Некорректный выбор." << std::endl;
                Utils::pressEnterToContinue();
                return;
        }
        saveMenu();
        std::cout << "Блюдо успешно обновлено." << std::endl;
    } else {
        std::cout << "Блюдо '" << nameToEdit << "' не найдено." << std::endl;
    }
    Utils::pressEnterToContinue();
}

void MenuManager::deleteDish() {
    Utils::clearScreen();
    std::cout << "--- Удаление блюда ---" << std::endl;
    displayMenu();
    std::string nameToDelete = Utils::getStringInput("Введите название блюда для удаления: ");

    auto it = dishes.begin();
    while (it != dishes.end()) {
        if (it->getName() == nameToDelete) {
            it = dishes.erase(it);
            saveMenu();
            std::cout << "Блюдо '" << nameToDelete << "' успешно удалено." << std::endl;
            Utils::pressEnterToContinue();
            return;
        }
        ++it;
    }
    std::cout << "Блюдо '" << nameToDelete << "' не найдено." << std::endl;
    Utils::pressEnterToContinue();
}

void MenuManager::displayMenu() const {
    if (dishes.empty()) {
        std::cout << "Меню пусто. Добавьте блюда." << std::endl;
        return;
    }
    std::cout << "\n--- Меню кафе ---" << std::endl;
    for (const auto& dish : dishes) {
        dish.display();
    }
    std::cout << "-----------------" << std::endl;
}

Dish* MenuManager::getDishByName(const std::string& name) {
    for (auto& dish : dishes) {
        if (dish.getName() == name) {
            return &dish;
        }
    }
    return nullptr; // Блюдо не найдено
}
