#include <iostream>
#include <vector>
#include <limits>
#include <locale>
#include <string>

using namespace std;

enum RunwayStatus {
    FREE = 0,
    OCCUPIED = 1
};

struct TicketSale {
    string passportNumber;
    double price;

    TicketSale(const string& passport, double p) : passportNumber(passport), price(p) {}

    ~TicketSale() {
        cout << "Деструктор для продажи билета: " << passportNumber << endl;
    }
};

struct Fare {
    string name;
    double price;

    Fare(const string& fareName, double farePrice) : name(fareName), price(farePrice) {}

    ~Fare() {
        cout << "Деструктор для тарифа: " << name << endl;
    }
};

static bool isValidNumber(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

template <typename T>
T getValidInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        cin >> input;

        if (isValidNumber(input)) {
            try {
                if constexpr (is_same<T, int>::value) {
                    return stoi(input);
                }
                else if constexpr (is_same<T, double>::value) {
                    return stod(input);
                }
            }
            catch (const invalid_argument& e) {
                cout << "Неверный ввод. Пожалуйста, введите только число." << endl;
            }
        }
        else {
            cout << "Неверный ввод. Пожалуйста, введите только число." << endl;
        }
    }
}

class Runway {
private:
    int id;
    RunwayStatus status;

public:
    Runway(int id, RunwayStatus status) : id(id), status(status) {}

    ~Runway() {
        cout << "Деструктор для взлетной полосы с ID: " << id << endl;
    }

    int getId() const { return id; }

    RunwayStatus getStatus() const { return status; }

    void setStatus(RunwayStatus newStatus) { status = newStatus; }

    void printInfo() const {
        cout << "Идентификатор взлетной полосы: " << id << " | "
            << (status == OCCUPIED ? "Занята" : "Свободна") << endl;
    }
};

class AirportCashier {
private:
    vector<Fare> fares;
    double totalSales;
    vector<TicketSale> sales;

public:
    AirportCashier() : totalSales(0.0) {}

    ~AirportCashier() {
        cout << "Деструктор для кассира аэропорта\n";
    }

    void addFare(const string& fareName, double farePrice) {
        fares.emplace_back(fareName, farePrice);
        cout << "Тариф добавлен успешно: " << fareName << " по цене " << farePrice << endl;
    }

    void printFares() const {
        cout << "Список тарифов:\n";
        for (size_t i = 0; i < fares.size(); ++i) {
            cout << i + 1 << ". " << fares[i].name << " - " << fares[i].price << endl;
        }
    }

    void registerSale(const string& passportNumber, double price) {
        totalSales += price;
        sales.emplace_back(passportNumber, price);
        cout << "Билет куплен на сумму: " << price << " (номер паспорта: " << passportNumber << ")\n";
    }

    double getTotalSales() const { return totalSales; }

    double getFarePrice(int index) const {
        if (index >= 0 && index < fares.size()) {
            return fares[index].price;
        }
        return 0.0;
    }
};

class Airport {
private:
    vector<Runway> runways;
    AirportCashier cashier;

    Airport() {}

    Airport(const Airport&) = delete;
    Airport& operator=(const Airport&) = delete;

public:
    static Airport& getInstance() {
        static Airport instance;
        return instance;
    }

    ~Airport() {
        cout << "Деструктор для аэропорта\n";
    }

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

    AirportCashier& getCashier() {
        return cashier;
    }
};

static void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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

        int choice = getValidInput<int>("Выберите опцию: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            int id = getValidInput<int>("Введите идентификатор взлетной полосы: ");
            int status = getValidInput<int>("Введите статус (0 для Свободна, 1 для Занята): ");
            airport.addRunway(id, static_cast<RunwayStatus>(status));
            break;
        }
        case 2: {
            int id = getValidInput<int>("Введите идентификатор взлетной полосы для обновления: ");
            int status = getValidInput<int>("Введите новый статус (0 для Свободна, 1 для Занята): ");
            airport.setRunwayStatus(id, static_cast<RunwayStatus>(status));
            break;
        }
        case 3:
            airport.printRunways();
            break;
        case 4: {
            string fareName;
            cout << "Введите название тарифа: ";
            getline(cin, fareName);
            double farePrice = getValidInput<double>("Введите цену тарифа: ");
            airport.getCashier().addFare(fareName, farePrice);
            break;
        }
        case 5:
            airport.getCashier().printFares();
            break;
        case 6: {
            string passport;
            cout << "Введите номер паспорта (только цифры): ";
            getline(cin, passport);
            airport.getCashier().printFares();
            int fareIndex = getValidInput<int>("Выберите тариф (введите номер): ") - 1;
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    setlocale(LC_ALL, "");
    menu();
    return 0;
}
