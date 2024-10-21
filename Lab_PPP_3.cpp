#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <memory>

using namespace std;

// Интерфейс для стратегии тарифа
class TariffStrategy {
public:
    virtual ~TariffStrategy() = default;
    // Метод для получения стоимости тарифа
    virtual double getCost() const = 0;
    virtual string getDestination() const = 0;
    // Новый метод: Исходная стоимость без скидок
    virtual double getOriginalCost() const = 0;
};

// Класс для тарифа без скидки
class NoDiscountTariff : public TariffStrategy {
private:
    string destination;
    double cost;
public:
    NoDiscountTariff(const string& dest, double c) : destination(dest), cost(c) {}

    double getCost() const override {
        return cost;
    }

    string getDestination() const override {
        return destination;
    }

    double getOriginalCost() const override {
        return cost; // Исходная стоимость такая же, так как скидок нет
    }
};

// Класс для тарифа с фиксированной скидкой
class FixedDiscountTariff : public TariffStrategy {
private:
    string destination;
    double cost;
    double discount;
public:
    FixedDiscountTariff(const string& dest, double c, double d) : destination(dest), cost(c), discount(d) {}

    double getCost() const override {
        return cost - discount;
    }

    string getDestination() const override {
        return destination;
    }

    double getOriginalCost() const override {
        return cost; // Возвращаем исходную стоимость без скидки
    }
};

// Новый класс для тарифа с процентной скидкой
class PercentageDiscountTariff : public TariffStrategy {
private:
    string destination;
    double cost;
    double percentage;
public:
    PercentageDiscountTariff(const string& dest, double c, double p) : destination(dest), cost(c), percentage(p) {}

    double getCost() const override {
        return cost * (1 - percentage / 100);
    }

    string getDestination() const override {
        return destination;
    }

    double getOriginalCost() const override {
        return cost; // Возвращаем исходную стоимость без скидки
    }
};

// Класс Аэропорт, который управляет тарифами
class Airport {
private:
    vector<shared_ptr<TariffStrategy>> tariffs;
public:
    bool doesTariffExist(const string& destination) const {
        for (const auto& tariff : tariffs) {
            if (tariff->getDestination() == destination) {
                return true;
            }
        }
        return false;
    }

    void addTariff(shared_ptr<TariffStrategy> tariff) {
        tariffs.push_back(tariff);
    }

    shared_ptr<TariffStrategy> getMaxCostTariff() const {
        if (tariffs.empty()) {
            throw runtime_error("Нет доступных тарифов");
        }

        shared_ptr<TariffStrategy> maxTariff = tariffs[0];
        for (const auto& tariff : tariffs) {
            if (tariff->getCost() > maxTariff->getCost()) {
                maxTariff = tariff;
            }
        }
        return maxTariff;
    }

    void removeTariffByDestination(const string& destination) {
        auto it = remove_if(tariffs.begin(), tariffs.end(),
            [&destination](const shared_ptr<TariffStrategy>& tariff) {
                return tariff->getDestination() == destination;
            });

        if (it != tariffs.end()) {
            tariffs.erase(it, tariffs.end());
            cout << "Тариф на направление \"" << destination << "\" был удалён.\n";
        }
        else {
            cout << "Тариф на данное направление не найден.\n";
        }
    }

    shared_ptr<TariffStrategy> findTariffByDestination(const string& destination) const {
        for (const auto& tariff : tariffs) {
            if (tariff->getDestination() == destination) {
                return tariff;
            }
        }
        throw runtime_error("Тариф на указанное направление не найден.");
    }

    void printAllTariffs() const {
        if (tariffs.empty()) {
            cout << "Список тарифов пуст.\n";
            return;
        }

        cout << "=== Список всех тарифов ===\n";
        for (const auto& tariff : tariffs) {
            cout << "Направление: " << tariff->getDestination()
                << " | Стоимость: " << tariff->getCost()
                << " | Исходная стоимость: " << tariff->getOriginalCost() << "\n";
        }
    }
};

// Функция для очистки консоли
static void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Функция для проверки корректного ввода числа
static double inputNumber(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите положительное число.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");

    Airport airport;
    int choice;

    while (true) {
        clearConsole();
        cout << "=== Меню аэропорта ===\n";
        cout << "1. Добавить новый тариф без скидки\n";
        cout << "2. Добавить новый тариф с фиксированной скидкой\n";
        cout << "3. Добавить новый тариф с процентной скидкой\n";
        cout << "4. Показать направление с максимальной стоимостью\n";
        cout << "5. Удалить тариф по направлению\n";
        cout << "6. Найти тариф по направлению\n";
        cout << "7. Показать все тарифы\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите корректный номер действия.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            clearConsole();
            string destination;
            cout << "Введите название направления: ";
            cin.ignore();
            getline(cin, destination);

            if (airport.doesTariffExist(destination)) {
                cout << "Ошибка: Тариф на данное направление уже существует. Введите другое название.\n";
                break;
            }

            double cost = inputNumber("Введите стоимость: ");
            airport.addTariff(make_shared<NoDiscountTariff>(destination, cost));
            cout << "Тариф добавлен успешно.\n";
            break;
        }
        case 2: {
            clearConsole();
            string destination;
            cout << "Введите название направления: ";
            cin.ignore();
            getline(cin, destination);

            if (airport.doesTariffExist(destination)) {
                cout << "Ошибка: Тариф на данное направление уже существует. Введите другое название.\n";
                break;
            }

            double cost = inputNumber("Введите стоимость: ");
            double discount = inputNumber("Введите размер скидки: ");
            if (cost < discount) {
                cout << "Ошибка: стоимость не может быть ниже скидки.\n";
                break;
            }
            airport.addTariff(make_shared<FixedDiscountTariff>(destination, cost, discount));
            cout << "Тариф с фиксированной скидкой добавлен успешно.\n";
            break;
        }
        case 3: {
            clearConsole();
            string destination;
            cout << "Введите название направления: ";
            cin.ignore();
            getline(cin, destination);

            if (airport.doesTariffExist(destination)) {
                cout << "Ошибка: Тариф на данное направление уже существует. Введите другое название.\n";
                break;
            }

            double cost = inputNumber("Введите стоимость: ");
            double percentage = inputNumber("Введите процент скидки: ");
            if (percentage < 0 || percentage > 100) {
                cout << "Ошибка: процент скидки должен быть от 0 до 100.\n";
                break;
            }
            airport.addTariff(make_shared<PercentageDiscountTariff>(destination, cost, percentage));
            cout << "Тариф с процентной скидкой добавлен успешно.\n";
            break;
        }
        case 4: {
            try {
                shared_ptr<TariffStrategy> maxTariff = airport.getMaxCostTariff();
                cout << "Направление с максимальной стоимостью: " << maxTariff->getDestination()
                    << " (Стоимость: " << maxTariff->getCost() << ")\n";
            }
            catch (const exception& e) {
                cout << e.what() << "\n";
            }
            break;
        }
        case 5: {
            clearConsole();
            string destination;
            cout << "Введите название направления для удаления: ";
            cin.ignore();
            getline(cin, destination);
            airport.removeTariffByDestination(destination);
            break;
        }
        case 6: {
            clearConsole();
            string destination;
            cout << "Введите название направления для поиска: ";
            cin.ignore();
            getline(cin, destination);
            try {
                shared_ptr<TariffStrategy> foundTariff = airport.findTariffByDestination(destination);
                cout << "Направление: " << foundTariff->getDestination()
                    << " | Стоимость: " << foundTariff->getCost() << "\n";
            }
            catch (const exception& e) {
                cout << e.what() << "\n";
            }
            break;
        }
        case 7: {
            airport.printAllTariffs();
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Ошибка: неверный выбор.\n";
        }
        cout << "\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}
