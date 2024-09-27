#include <iostream>
#include <vector>
#include <limits>
#include <locale>
#include <string>

using namespace std;

// Перечисление 
enum RunwayStatus {
    FREE = 0,
    OCCUPIED = 1
};

// Структура для хранения информации о продаже билета
struct TicketSale {
    string passportNumber;
    double price;

    TicketSale(const string& passport, double p) : passportNumber(passport), price(p) {}
};

// Структура для хранения тарифов
struct Fare {
    string name;
    double price;

    Fare(const string& fareName, double farePrice) : name(fareName), price(farePrice) {}
};

// Взлетная полоса
class Runway {
private:
    int id;
    RunwayStatus status;

public:
    Runway(int id, RunwayStatus status) : id(id), status(status) {}

    int getId() const { return id; }

    RunwayStatus getStatus() const { return status; }

    void setStatus(RunwayStatus newStatus) { status = newStatus; }

    // Вывод информации о полосе
    void printInfo() const {
        cout << "Идентификатор взлетной полосы: " << id << " | "
            << (status == OCCUPIED ? "Занята" : "Свободна") << endl;
    }
};

class AirportCashier {
private:
    vector<Fare> fares; // Список тарифов
    double totalSales;
    vector<TicketSale> sales;

public:
    AirportCashier() : totalSales(0.0) {}

    // Метод для добавления нового тарифа
    void addFare(const string& fareName, double farePrice) {
        fares.emplace_back(fareName, farePrice);
        cout << "Тариф добавлен успешно: " << fareName << " по цене " << farePrice << endl;
    }

    // Метод для вывода тарифов
    void printFares() const {
        cout << "Список тарифов:\n";
        for (size_t i = 0; i < fares.size(); ++i) {
            cout << i + 1 << ". " << fares[i].name << " - " << fares[i].price << endl;
        }
    }

    // Метод для регистрации покупки билета
    void registerSale(const string& passportNumber, double price) {
        totalSales += price;
        sales.emplace_back(passportNumber, price);
        cout << "Билет куплен на сумму: " << price << " (номер паспорта: " << passportNumber << ")\n";
    }

    double getTotalSales() const { return totalSales; }

    // Метод для получения цены тарифа по индексу
    double getFarePrice(int index) const {
        if (index >= 0 && index < fares.size()) {
            return fares[index].price;
        }
        return 0.0; // Возвращаем 0, если индекс невалиден
    }
};

// Класс Singleton для управления аэропортом
class Airport {
private:
    vector<Runway> runways;
    AirportCashier cashier;

    // Приватный конструктор для Singleton
    Airport() {}

    Airport(const Airport&) = delete;
    Airport& operator=(const Airport&) = delete;

public:
    // Метод для получения единственного экземпляра класса (Singleton)
    static Airport& getInstance() {
        static Airport instance;
        return instance;
    }

    // Метод для проверки, существует ли полоса с данным ID
    bool runwayExists(int id) const {
        for (const auto& runway : runways) {
            if (runway.getId() == id) {
                return true;
            }
        }
        return false;
    }

    void addRunway(int id, RunwayStatus status) {
        if (runwayExists(id)) {
            cout << "Ошибка: Взлетная полоса с идентификатором " << id << " уже существует!\n";
        }
        else {
            runways.emplace_back(id, status);
            cout << "Взлетная полоса добавлена успешно.\n";
        }
    }

    void printRunways() const {
        for (const auto& runway : runways) {
            runway.printInfo();
        }
    }

    void setRunwayStatus(int id, RunwayStatus newStatus) {
        for (auto& runway : runways) {
            if (runway.getId() == id) {
                runway.setStatus(newStatus);
                cout << "Статус взлетной полосы " << id << " обновлён.\n";
                return;
            }
        }
        cout << "Взлетная полоса " << id << " не найдена.\n";
    }

    static int inputInteger(const string& prompt) {
        int num;
        while (true) {
            cout << prompt;
            cin >> num;

            if (cin.fail() || num < 0) { // Проверка на ввод отрицательных чисел
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный ввод. Пожалуйста, введите неотрицательное число.\n";
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return num;
            }
        }
    }

    static double inputDouble(const string& prompt) {
        double num;
        while (true) {
            cout << prompt;
            cin >> num;

            if (cin.fail() || num < 0.0) { // Проверка на ввод отрицательных чисел
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный ввод. Пожалуйста, введите неотрицательное число.\n";
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return num;
            }
        }
    }

    static string inputString(const string& prompt) {
        string input;
        cout << prompt;
        getline(cin, input);
        return input;
    }

    AirportCashier& getCashier() {
        return cashier;
    }
};

void clearConsole() {
#ifdef _WIN32
    system("cls"); // Для Windows
#else
    system("clear"); // Для Linux/macOS
#endif
}

// Главное меню
static void menu() {
    Airport& airport = Airport::getInstance();
    bool OnDisplay = true;

    while (OnDisplay) {
        clearConsole();

        cout << "===== Система управления аэропортом =====\n";
        cout << "1. Добавить новую взлетную полосу\n";
        cout << "2. Обновить статус взлетной полосы\n";
        cout << "3. Просмотреть все взлетные полосы\n";
        cout << "4. Добавить новый тариф\n";
        cout << "5. Просмотреть все тарифы\n";
        cout << "6. Купить билет\n";
        cout << "7. Просмотреть общую сумму продаж\n";
        cout << "0. Выход\n";
        cout << "=========================================\n";

        int choice = Airport::inputInteger("Выберите опцию: ");

        switch (choice) {
        case 1: {
            int id = Airport::inputInteger("Введите идентификатор взлетной полосы: ");
            int status = Airport::inputInteger("Введите статус (0 для Свободна, 1 для Занята): ");
            airport.addRunway(id, static_cast<RunwayStatus>(status));
            break;
        }
        case 2: {
            int id = Airport::inputInteger("Введите идентификатор взлетной полосы для обновления: ");
            int status = Airport::inputInteger("Введите новый статус (0 для Свободна, 1 для Занята): ");
            airport.setRunwayStatus(id, static_cast<RunwayStatus>(status));
            break;
        }
        case 3:
            airport.printRunways();
            break;
        case 4: {
            string fareName = Airport::inputString("Введите название тарифа: ");
            double farePrice = Airport::inputDouble("Введите цену тарифа: "); // Обновлено на inputDouble
            airport.getCashier().addFare(fareName, farePrice);
            break;
        }
        case 5:
            airport.getCashier().printFares();
            break;
        case 6: {
            string passport = Airport::inputString("Введите номер паспорта (только цифры): ");
            airport.getCashier().printFares();
            int fareIndex = Airport::inputInteger("Выберите тариф (введите номер): ") - 1;
            double farePrice = airport.getCashier().getFarePrice(fareIndex);
            airport.getCashier().registerSale(passport, farePrice);
            break;
        }
        case 7:
            cout << "Общая сумма продаж: " << airport.getCashier().getTotalSales() << endl;
            break;
        case 0:
            OnDisplay = false;
            break;
        default:
            cout << "Неверный выбор! Пожалуйста, попробуйте снова.\n";
        }

        cout << "\nНажмите Enter, чтобы продолжить...";
        cin.get();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}
