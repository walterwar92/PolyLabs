#include <iostream>
#include <windows.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
// Типы функций
typedef void (*CallbackType)(int messageType, double x, double fx, double Fx, double delta);
typedef const char* (*GetFunctionNameType)();
typedef void (*CalculateType)(double x_start, double x_end, double dx, double epsilon, CallbackType callback);

// Константы ширины колонок
const int COLUMN_WIDTH = 20;

// Функция для печати горизонтальной линии
void printSeparator(int columns) {
    for (int i = 0; i < columns; ++i) {
        cout << "+";
        for (int j = 0; j < COLUMN_WIDTH; ++j) {
            cout << "-";
        }
    }
    cout << "+" << endl;
}

// Функция для печати строки таблицы
void printRow(const vector<string>& row) {
    for (const auto& cell : row) {
        cout << "| " << setw(COLUMN_WIDTH - 2) << right << cell;
    }
    cout << "|" << endl;
}

// Функция для форматирования числа в строку с фиксированной шириной
string formatNumber(double number) {
    ostringstream oss;
    oss << fixed << setprecision(6) << number; // Устанавливаем фиксированное количество знаков после запятой
    return oss.str();
}

// Функция обратного вызова
void callback(int messageType, double x, double fx, double Fx, double delta) {
    static bool headerPrinted = false;

    if (!headerPrinted) {
        printSeparator(4);
        printRow({"x", "f(x)", "F(x)", "delta"});
        headerPrinted = true;
    }

    switch (messageType) {
        case 1: {
            printRow({formatNumber(x), formatNumber(fx), formatNumber(Fx), formatNumber(delta)});
            break;
        }
        case 2: {
            cerr << "Error calculating at x = " << x << endl;
            break;
        }
    }
}

int main() {
    // Загрузка библиотеки
    HINSTANCE hinstLib = LoadLibrary(TEXT("libMathLibrary.dll"));
    if (!hinstLib) {
        cerr << "Unable to load library!" << endl;
        return 1;
    }

    // Загрузка функций из библиотеки
    GetFunctionNameType getFunctionName = (GetFunctionNameType)GetProcAddress(hinstLib, "getFunctionName");
    CalculateType calculate = (CalculateType)GetProcAddress(hinstLib, "calculate");

    if (!getFunctionName || !calculate) {
        cerr << "Unable to find functions!" << endl;
        FreeLibrary(hinstLib);
        return 1;
    }

    cout << "Function: " << getFunctionName() << endl;

    // Ввод данных от пользователя
    double x_start, x_end, dx, epsilon;
    cout << "Enter start of interval: ";
    cin >> x_start;
    cout << "Enter end of interval: ";
    cin >> x_end;
    cout << "Enter step: ";
    cin >> dx;
    cout << "Enter precision: ";
    cin >> epsilon;

    // Вызов функции расчета
    calculate(x_start, x_end, dx, epsilon, callback);

    // Печать нижней границы таблицы
    printSeparator(4);

    // Освобождение библиотеки
    FreeLibrary(hinstLib);
    return 0;
}
