#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Рядная функция
double f(double x, int n) {
    double result = 1.0;
    double term = 1.0;
    for (int i = 1; i <= n; ++i) {
        term *= (-1) * x * x / (2 * i * (2 * i - 1));
        result += term;
    }
    return result;
}

int main() {
    double epsilon, x_start, x_end, delta_x, x_ideal;
    cout << "Введите точность ε (от 1e-1 до 1e-7): ";
    while (!(cin >> epsilon) || epsilon < 1e-7 || epsilon > 1e-1) {
        cout << "Ошибка! Пожалуйста, введите точность ε от 1e-1 до 1e-7: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите начало отрезка x_start: ";
    while (!(cin >> x_start)) {
        cout << "Ошибка! Пожалуйста, введите числовое значение для начала отрезка x_start: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите конец отрезка x_end: ";
    while (!(cin >> x_end)) {
        cout << "Ошибка! Пожалуйста, введите числовое значение для конца отрезка x_end: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите шаг Δx: ";
    while (!(cin >> delta_x)) {
        cout << "Ошибка! Пожалуйста, введите числовое значение для шага Δx: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите значение x_ideal: ";
    while (!(cin >> x_ideal)) {
        cout << "Ошибка! Пожалуйста, введите числовое значение для x_ideal: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << setw(13) << "Таблица 1:" << endl;
    cout << setw(15) << "x" << " | " << setw(15) << "f(x)" << " | " << setw(15) << "F(x)" << " | " << setw(15) << "δ" << endl;
    
    for (double x = x_start; x <= x_end; x += delta_x) {
        double f_value = f(x, 50); // Вычисляем значение рядной функции
        double F_value = cos(x) * cos(x); // Вычисляем значение библиотечной функции
        double delta = sqrt(fabs(f_value * f_value - F_value)); // Вычисляем невязку
        
        cout << scientific << setw(15) << setprecision(6) << x << " | " << (fabs(f_value) > 1e-10 ? scientific : fixed) << setw(15) << f_value << " | " 
             << (fabs(F_value) > 1e-10 ? scientific : fixed) << setw(15) << F_value << " | " << scientific << setw(15) << delta << endl;
    }

    cout << setw(13) << "Таблица 2:" << endl;
    cout << setw(15) << "ε" << " | " << setw(15) << "f(x_ideal)" << " | " << setw(15) << "F(x_ideal)" << " | " << setw(15) << "δ" << endl;

    for (int i = 1; i <= 7; ++i) {
        double current_epsilon = pow(10, -i);
        double f_ideal = f(x_ideal, 50); // Вычисляем значение рядной функции для x_ideal
        double F_ideal = cos(x_ideal) * cos(x_ideal); // Вычисляем значение библиотечной функции для x_ideal
        double delta_ideal = sqrt(fabs(f_ideal * f_ideal - F_ideal)); // Вычисляем невязку для x_ideal
        
        cout << scientific << setw(15) << setprecision(7) << current_epsilon << " | " 
             << (fabs(f_ideal) > 1e-10 ? scientific : fixed) << setw(15) << f_ideal << " | " 
             << (fabs(F_ideal) > 1e-10 ? scientific : fixed) << setw(15) << F_ideal << " | " 
             << scientific << setw(15) << delta_ideal << endl;
    }

    return 0;
}
