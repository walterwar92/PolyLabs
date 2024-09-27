#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Класс Runway (Взлетная полоса)
class Runway {
private:
    int id; // Идентификатор взлетной полосы
    bool isOccupied; // Статус: занята или свободна

public:
    // Конструктор с параметрами
    Runway(int id, bool isOccupied) : id(id), isOccupied(isOccupied) {}

    // Метод для получения идентификатора полосы
    int getId() const { return id; }

    // Метод для проверки занята ли полоса
    bool getOccupiedStatus() const { return isOccupied; }

    // Метод для изменения статуса полосы
    void setOccupiedStatus() { isOccupied = !isOccupied; }

    // Вывод информации о полосе
    void printInfo() const {
        cout << "Runway ID: " << id << " | "
            << (isOccupied ? "Occupied" : "Free") << endl;
    }
};

// Класс Singleton для управления аэропортом
class Airport {
private:
    vector<Runway> runways; // Контейнер для взлетных полос

    // Приватный конструктор для Singleton
    Airport() {}

    // Запрет копирования и присваивания
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

    // Метод для добавления новой взлетной полосы с проверкой на уникальность ID
    void addRunway(int id, bool isOccupied) {
        if (runwayExists(id)) {
            cout << "Error: Runway with ID " << id << " already exists!\n";
        }
        else {
            runways.emplace_back(id, isOccupied);
            cout << "Runway added successfully.\n";
        }
    }

    // Метод для вывода информации о всех взлетных полосах
    void printRunways() const {
        for (const auto& runway : runways) {
            runway.printInfo();
        }
    }

    // Метод для изменения статуса взлетной полосы
    void setRunwayStatus(int id) {
        for (auto& runway : runways) {
            if (runway.getId() == id) {
                runway.setOccupiedStatus();
                cout << "Runway " << id << " status updated.\n";
                return;
            }
        }
        cout << "Runway " << id << " not found.\n";
    }

    // Метод для безопасного ввода чисел
    static int inputInteger(const string& prompt) {
        int num;
        while (true) {
            cout << prompt;
            cin >> num;

            if (cin.fail()) {
                cin.clear(); // Сбросить флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистить буфер
                cout << "Invalid input. Please enter a valid number.\n";
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистить оставшийся ввод
                return num;
            }
        }
    }
};

// Функция для очистки консоли
void clearConsole() {
    // Для Windows
#ifdef _WIN32
    system("cls");
    // Для Linux/macOS
#else
    system("clear");
#endif
}

// Главное меню
static void menu() {
    Airport& airport = Airport::getInstance();
    bool OnDisplay = true;

    while (OnDisplay) {
        clearConsole(); // Очистка консоли перед выводом меню

        cout << "===== Airport Management System =====\n";
        cout << "1. Add a new runway\n";
        cout << "2. Update runway status\n";
        cout << "3. View all runways\n";
        cout << "0. Exit\n";
        cout << "=====================================\n";

        int choice = Airport::inputInteger("Select an option: ");

        switch (choice) {
        case 1: {
            int id = Airport::inputInteger("Enter the runway ID: ");
            int status = Airport::inputInteger("Enter the status (0 for Free, 1 for Occupied): ");
            airport.addRunway(id, status);
            break;
        }
        case 2: {
            int id = Airport::inputInteger("Enter the runway ID to update: ");
            airport.setRunwayStatus(id);
            break;
        }
        case 3:
            airport.printRunways();
            break;
        case 0:
            OnDisplay = false;
            break;
        default:
            cout << "Invalid option! Please try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

int main() {
    menu();
    return 0;
}
