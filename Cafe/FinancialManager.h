#pragma once

#include "OrderManager.h" // Для доступа к заказам
#include <string>
#include <map> // Для хранения прибыли по дням
#include <fstream>
#include <ctime> // Для работы с датами

class FinancialManager {
private:
    OrderManager& orderManager; // Ссылка на менеджер заказов
    std::map<std::string, double> dailyProfits; // Дата (YYYY-MM-DD) -> Прибыль
    const std::string PROFITS_FILENAME = "profits.txt";
    const std::string REPORT_FILENAME = "report.txt";

    void loadProfits();
    void saveProfits();
    std::string getCurrentDate(); // Вспомогательная функция для получения текущей даты

public:
    FinancialManager(OrderManager& orderMgr);

    void recordDailyProfit();
    void generateSummary() const;
    void generateReport() const;
};
