#include "FinancialManager.h"
#include "Utils.h"
#include <sstream>
#include <algorithm> // Для std::sort

FinancialManager::FinancialManager(OrderManager& orderMgr) : orderManager(orderMgr) {
    loadProfits();
}

void FinancialManager::loadProfits() {
    std::ifstream inFile(PROFITS_FILENAME);
    if (!inFile.is_open()) {
        std::cerr << "Информация: Файл прибыли " << PROFITS_FILENAME << " не найден или пуст." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string date;
        double profit;
        char comma; // Для пропуска запятой

        if (std::getline(ss, date, ',') && (ss >> profit)) {
            dailyProfits[date] = profit;
        }
    }
    inFile.close();
}

void FinancialManager::saveProfits() {
    std::ofstream outFile(PROFITS_FILENAME);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << PROFITS_FILENAME << " для записи." << std::endl;
        return;
    }
    for (const auto& entry : dailyProfits) {
        outFile << entry.first << "," << entry.second << "\n";
    }
    outFile.close();
}

std::string FinancialManager::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d");
    return ss.str();
}

void FinancialManager::recordDailyProfit() {
    Utils::clearScreen();
    std::cout << "--- Учет ежедневной прибыли ---" << std::endl;

    std::string today = getCurrentDate();
    double currentDayProfit = 0.0;
    int ordersCount = 0;

    const auto& allOrders = orderManager.getAllOrders();
    for (const auto& order : allOrders) {
        // Проверяем, что заказ не отменен и был сделан сегодня
        // Примечание: Это упрощение. В реальной системе "завершенные" заказы могут быть помечены иначе,
        // а не просто "не отмененные".
        if (!order.isCancelled() && order.getTimestamp().rfind(today, 0) == 0) { // Проверяем, начинается ли timestamp с сегодняшней даты
            currentDayProfit += order.getTotalAmount();
            ordersCount++;
        }
    }

    dailyProfits[today] = currentDayProfit;
    saveProfits();

    std::cout << "Прибыль за " << today << ": " << currentDayProfit << " руб. (из " << ordersCount << " завершенных заказов)" << std::endl;
    Utils::pressEnterToContinue();
}

void FinancialManager::generateSummary() const {
    Utils::clearScreen();
    std::cout << "--- Финансовая сводка ---" << std::endl;

    double totalProfit = 0.0;
    if (dailyProfits.empty()) {
        std::cout << "Данных о прибыли нет." << std::endl;
    } else {
        std::cout << "Прибыль по дням:\n";
        for (const auto& entry : dailyProfits) {
            std::cout << "  " << entry.first << ": " << entry.second << " руб.\n";
            totalProfit += entry.second;
        }
    }

    std::cout << "\nВсего заказов в системе: " << orderManager.getAllOrders().size() << std::endl;
    int cancelledOrders = 0;
    int completedOrders = 0;
    for(const auto& order : orderManager.getAllOrders()) {
        if(order.isCancelled()) {
            cancelledOrders++;
        } else {
            completedOrders++;
        }
    }
    std::cout << "Завершенных заказов: " << completedOrders << std::endl;
    std::cout << "Отмененных заказов: " << cancelledOrders << std::endl;

    // Сводка по проданным блюдам
    std::map<std::string, int> dishSalesCount;
    std::map<std::string, double> dishSalesRevenue;

    for (const auto& order : orderManager.getAllOrders()) {
        if (!order.isCancelled()) {
            for (const auto& item : order.getItems()) {
                dishSalesCount[item.dishName] += item.quantity;
                dishSalesRevenue[item.dishName] += item.pricePerUnit * item.quantity;
            }
        }
    }

    if (!dishSalesCount.empty()) {
        std::cout << "\nПродажи блюд:\n";
        for (const auto& entry : dishSalesCount) {
            std::cout << "  " << entry.first << ": " << entry.second << " шт. (На сумму: "
                      << dishSalesRevenue[entry.first] << " руб.)\n";
        }
    } else {
        std::cout << "\nНет данных о продажах блюд." << std::endl;
    }

    std::cout << "\nОбщая прибыль за все время: " << totalProfit << " руб." << std::endl;
    std::cout << "-------------------------" << std::endl;
    Utils::pressEnterToContinue();
}

void FinancialManager::generateReport() const {
    Utils::clearScreen();
    std::cout << "--- Генерация финансового отчета ---" << std::endl;

    std::ofstream outFile(REPORT_FILENAME);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << REPORT_FILENAME << " для записи." << std::endl;
        Utils::pressEnterToContinue();
        return;
    }

    outFile << "Финансовый отчет кафе (" << getCurrentDate() << ")\n";
    outFile << "-------------------------------------------\n\n";

    double totalProfit = 0.0;
    if (dailyProfits.empty()) {
        outFile << "Данных о прибыли нет.\n";
    } else {
        outFile << "Прибыль по дням:\n";
        for (const auto& entry : dailyProfits) {
            outFile << "  " << entry.first << ": " << entry.second << " руб.\n";
            totalProfit += entry.second;
        }
    }

    outFile << "\nОбщая прибыль за все время: " << totalProfit << " руб.\n";
    outFile << "\n-------------------------------------------\n";
    outFile << "Статистика заказов:\n";
    outFile << "Всего заказов в системе: " << orderManager.getAllOrders().size() << "\n";
    int cancelledOrders = 0;
    int completedOrders = 0;
    for(const auto& order : orderManager.getAllOrders()) {
        if(order.isCancelled()) {
            cancelledOrders++;
        } else {
            completedOrders++;
        }
    }
    outFile << "Завершенных заказов: " << completedOrders << "\n";
    outFile << "Отмененных заказов: " << cancelledOrders << "\n";

    // Сводка по проданным блюдам
    std::map<std::string, int> dishSalesCount;
    std::map<std::string, double> dishSalesRevenue;

    for (const auto& order : orderManager.getAllOrders()) {
        if (!order.isCancelled()) {
            for (const auto& item : order.getItems()) {
                dishSalesCount[item.dishName] += item.quantity;
                dishSalesRevenue[item.dishName] += item.pricePerUnit * item.quantity;
            }
        }
    }

    if (!dishSalesCount.empty()) {
        outFile << "\nПродажи блюд:\n";
        for (const auto& entry : dishSalesCount) {
            outFile << "  " << entry.first << ": " << entry.second << " шт. (На сумму: "
                      << dishSalesRevenue[entry.first] << " руб.)\n";
        }
    } else {
        outFile << "\nНет данных о продажах блюд.\n";
    }

    outFile << "-------------------------------------------\n";
    outFile.close();
    std::cout << "Финансовый отчет успешно сохранен в файл " << REPORT_FILENAME << std::endl;
    Utils::pressEnterToContinue();
}
