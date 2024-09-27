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
        cout << "Идентификатор взлетной полосы: " << id << " | "
            << (isOccupied ? "Занята" : "Свободна") << endl;
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
            cout << "Ошибка: Взлетная полоса с идентификатором " << id << " уже существует!\n";
        }
        else {
            runways.emplace_back(id, isOccupied);
            cout << "Взлетная полоса добавлена успешно.\n";
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
                cout << "Статус взлетной полосы " << id << " обновлён.\n";
                return;
            }
        }
        cout << "Взлетная полоса " << id << " не найдена.\n";
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
                cout << "Неверный ввод. Пожалуйста, введите корректное число.\n";
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

        cout << "===== Система управления аэропортом =====\n";
        cout << "1. Добавить новую взлетную полосу\n";
        cout << "2. Обновить статус взлетной полосы\n";
        cout << "3. Просмотреть все взлетные полосы\n";
        cout << "0. Выход\n";
        cout << "=========================================\n";

        int choice = Airport::inputInteger("Выберите опцию: ");

        switch (choice) {
        case 1: {
            int id = Airport::inputInteger("Введите идентификатор взлетной полосы: ");
            int status = Airport::inputInteger("Введите статус (0 для Свободна, 1 для Занята): ");
            airport.addRunway(id, status);
            break;
        }
        case 2: {
            int id = Airport::inputInteger("Введите идентификатор взлетной полосы для обновления: ");
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
            cout << "Неверная опция! Пожалуйста, попробуйте снова.\n";
        }

        cout << "\nНажмите Enter, чтобы продолжить...";
        cin.get();
    }
}

int main() {
    menu();
    return 0;
}
