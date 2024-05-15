#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <functional>
#include <limits>
#include <random> // для генерации случайной соли

using namespace std;

// Функция для хэширования пароля с использованием std::hash и соли
size_t hashPassword(const string& password, const string& salt) {
    string saltedPassword = salt + password;
    return hash<string>{}(saltedPassword); // используем стандартную функцию хэширования
}

// Функция загрузки базы данных из файла
unordered_map<string, pair<string, size_t>> loadDatabase(const string& filename) {
    unordered_map<string, pair<string, size_t>> database; // создаем контейнер для хранения пар "имя пользователя - (соль, хэш пароля)"
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file" << filename << endl;
        return database;
    }

    string username, salt;
    size_t password_hash;
    while (file >> username >> salt >> password_hash) {
        database[username] = {salt, password_hash};
    }

    file.close();
    return database;
}

// Функция сохранения базы данных в файл
bool saveDatabase(const string& filename, const unordered_map<string, pair<string, size_t>>& database) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    for (const auto& pair : database) {
        file << pair.first << " " << pair.second.first << " " << pair.second.second << endl;
    }

    file.close();
    return true;
}

// Функция для генерации случайной соли
string generateSalt() {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    int len = 16;
    string salt;
    random_device rd; // генератор случайных чисел
    mt19937 gen(rd()); // инициализация генератора
    uniform_int_distribution<> dis(0, sizeof(alphanum) - 2); // диапазон значений

    for (int i = 0; i < len; ++i) {
        salt += alphanum[dis(gen)];
    }
    return salt;
}

// Функция для добавления нового пользователя
void addUser(unordered_map<string, pair<string, size_t>>& database, const string& username, const string& password) {
    if (database.find(username) != database.end()) {
        cerr << "Error: Username already exists." << endl;
        return;
    }

    string salt = generateSalt();
    size_t password_hash = hashPassword(password, salt);
    database[username] = {salt, password_hash};
    cout << "User added successfully." << endl;
}

// Функция для аутентификации пользователя
bool authenticateUser(const unordered_map<string, pair<string, size_t>>& database, const string& username, const string& password) {
    auto it = database.find(username);
    if (it == database.end()) {
        cerr << "Error: Username not found." << endl;
        return false;
    }

    string salt = it->second.first;
    size_t password_hash = hashPassword(password, salt);
    if (it->second.second == password_hash) {
        cout << "Authentication successful." << endl;
        return true;
    } else {
        cerr << "Error: Incorrect password." << endl;
        return false;
    }
}

// Главная функция программы
int main() {
    string filename = "C:/Users/Roman/Desktop/users.txt";
    auto database = loadDatabase(filename);

    while (true) {
        cout << "1. Add User\n2. Authenticate User\n3. Exit\nEnter your choice:";
        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3) {
            cerr << "Invalid input. Please enter a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string username, password;
            cout << "Enter username:";
            getline(cin, username);
            cout << "Enter password:";
            getline(cin, password);
            addUser(database, username, password);
            saveDatabase(filename, database);
        } else if (choice == 2) {
            string username, password;
            cout << "Enter username:";
            getline(cin, username);
            cout << "Enter password:";
            getline(cin, password);
            authenticateUser(database, username, password);
        } else if (choice == 3) {
            break;
        }
    }

    return 0;
}
