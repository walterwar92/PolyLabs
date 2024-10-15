#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

// Интерфейс для стратегии тарифа
class TariffStrategy {
public:
    virtual ~TariffStrategy() = default;
    // Метод для получения стоимости тарифа
    virtual double getCost() const = 0;
    virtual string getDestination() const = 0;
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
};

// Класс Аэропорт, который управляет тарифами
class Airport {
private:
    vector<shared_ptr<TariffStrategy>> tariffs;
public:
    // Проверка на существующее направление
    bool doesTariffExist(const string& destination) const {
        for (const auto& tariff : tariffs) {
            if (tariff->getDestination() == destination) {
                return true;
            }
        }
        return false;
    }
    // Метод для добавления нового тарифа
    void addTariff(shared_ptr<TariffStrategy> tariff) {
        tariffs.push_back(tariff);
    }

    // Метод для поиска направления с максимальной стоимостью
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

    // Новый метод: Удаление тарифа по названию направления
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

    // Новый метод: Поиск тарифа по названию направления
    shared_ptr<TariffStrategy> findTariffByDestination(const string& destination) const {
        for (const auto& tariff : tariffs) {
            if (tariff->getDestination() == destination) {
                return tariff;
            }
        }
        throw runtime_error("Тариф на указанное направление не найден.");
    }

    // Новый метод: Вывод всех тарифов
    void printAllTariffs() const {
        if (tariffs.empty()) {
            cout << "Список тарифов пуст.\n";
            return;
        }

        cout << "=== Список всех тарифов ===\n";
        for (const auto& tariff : tariffs) {
            cout << "Направление: " << tariff->getDestination()
                << " | Стоимость: " << tariff->getCost() << "\n";
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
        cout << "3. Показать направление с максимальной стоимостью\n";
        cout << "4. Удалить тариф по направлению\n";
        cout << "5. Найти тариф по направлению\n";
        cout << "6. Показать все тарифы\n";
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

            // Проверка на существующее направление
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

            // Проверка на существующее направление
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
        case 4: {
            clearConsole();
            string destination;
            cout << "Введите название направления для удаления: ";
            cin.ignore();
            getline(cin, destination);
            airport.removeTariffByDestination(destination);
            break;
        }
        case 5: {
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
        case 6: {
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
