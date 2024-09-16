#include <iostream>
#include <string>
#include <cstdlib> // для system("cls") / system("clear")
#include <limits>

using namespace std;

class Airport {
private:
    string name;         // Название аэропорта
    double ticketPrice;  // Стоимость билета
    int totalSeats;      // Общее количество мест во всех самолетах
    int soldTickets;     // Количество проданных билетов

public:
    Airport(const string& airportName, double price, int seats)
        : name(airportName), ticketPrice(price), totalSeats(seats), soldTickets(0) {}

    void sellTickets(int number) {
        if (number <= (totalSeats - soldTickets)) {
            soldTickets += number;
            cout << "Sold " << number << " tickets." << endl;
        }
        else {
            cout << "There are not enough available places for sale " << number << " tickets." << endl;
        }
    }

    double calculateTotalRevenue() const {
        return soldTickets * ticketPrice;
    }

    void displayInfo() const {
        cout << "Airport: " << name << endl;
        cout << "Ticket cost: " << ticketPrice << endl;
        cout << "Total number of seats: " << totalSeats << endl;
        cout << "Tickets sold: " << soldTickets << endl;
        cout << "Total cost of tickets sold: " << calculateTotalRevenue() << endl;
    }
};

void clearConsole() {
#ifdef _WIN32
    system("cls");  // Очистка консоли для Windows
#else
    system("clear"); // Очистка консоли для Linux/Unix
#endif
}

bool isValidNumber(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Функция для безопасного ввода числа с проверкой на некорректный ввод
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
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }
        else {
            cout << "Invalid input. Please enter only numbers." << endl;
        }
    }
}

int main() {
    Airport* airport = nullptr;
    bool OnDisplay = true;
    short int choice;

    while (OnDisplay) {
        clearConsole();
        cout << "Database Administrator Console:\n";
        cout << "1. To add a new airport to the database.\n";
        cout << "2. Current information about the airport.\n";
        cout << "3. Calculating total revenue.\n";
        cout << "4. Sell tickets.\n";
        cout << "5. Exit.\n";

       cout << "Enter your choice: "; 
       cin >> choice;

        switch (choice) {
        case 1: {
            clearConsole();
            string airportname;
            double airportprice;
            int airportseats;

            cout << "Enter the name of the airport: ";
            cin >> airportname;
            airportprice = getValidInput<double>("Enter the ticket price: ");
            airportseats = getValidInput<int>("Enter the total number of seats: ");

            // Создаем новый аэропорт
            airport = new Airport(airportname, airportprice, airportseats);
            cout << "Airport added successfully!" << endl;
            break;
        }
        case 2: {
            clearConsole();
            if (airport) {
                airport->displayInfo();
            }
            else {
                cout << "No airport data available. Please add an airport first." << endl;
            }
            break;
        }
        case 3: {
            clearConsole();
            if (airport) {
                cout << "Total revenue: " << airport->calculateTotalRevenue() << endl;
            }
            else {
                cout << "No airport data available. Please add an airport first." << endl;
            }
            break;
        }
        case 4: {
            clearConsole();
            if (airport) {
                int ticketsToSell = getValidInput<int>("Enter the number of tickets to sell: "); // безопасный ввод
                airport->sellTickets(ticketsToSell);
            }
            else {
                cout << "No airport data available. Please add an airport first." << endl;
            }
            break;
        }
        case 5: {
            clearConsole();
            cout << "Exiting the program..." << endl;
            OnDisplay = false;
            break;
        }
        default: {
            clearConsole();
            cout << "Invalid choice. Please try again." << endl;
        }
        }


        if (OnDisplay) {
            cout << "Press Enter to continue...";
            cin.ignore(); // Игнорируем символ новой строки после ввода числа
            cin.get(); // Ожидаем нажатия клавиши
        }
    }


    if (airport) {
        delete airport;
    }

    return 0;
}
