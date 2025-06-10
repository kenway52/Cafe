#include "Dish.h"
#include <vector>
#include <string>
#include <fstream> // Для работы с файлами

class MenuManager {
private:
    std::vector<Dish> dishes;
    const std::string FILENAME = "menu.txt";

    void saveMenu(); // Приватный метод, вызывается после изменений
    void loadMenu(); // Приватный метод, вызывается при инициализации

public:
    MenuManager(); // Конструктор, загружающий меню

    void addDish();
    void editDish();
    void deleteDish();
    void displayMenu() const;

    // Вспомогательные методы для других менеджеров
    Dish* getDishByName(const std::string& name);
};
