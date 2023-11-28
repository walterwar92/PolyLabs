#include <iostream>
#include <cmath>
#include <iomanip>

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
    cout << "Введите точность ε: ";
    cin >> epsilon;
    cout << "Введите начало отрезка x_start: ";
    cin >> x_start;
    cout << "Введите конец отрезка x_end: ";
    cin >> x_end;
    cout << "Введите шаг Δx: ";
    cin >> delta_x;
    cout << "Введите значение x_ideal: ";
    cin >> x_ideal;

    cout << setw(13) << "Таблица 1:" << endl;
    cout << setw(15) << "x" << " | " << setw(15) << "f(x)" << " | " << setw(15) << "F(x)" << " | " << setw(15) << "δ" << endl;
    
    for (double x = x_start; x <= x_end; x += delta_x) {
        double f_value = f(x, 50); // Вычисляем значение рядной функции
        double F_value = cos(x) * cos(x); // Вычисляем значение библиотечной функции
        double delta = sqrt(fabs(f_value * f_value - F_value)); // Вычисляем невязку
        
        cout << setw(15) << setprecision(6) << x << " | " << setw(15) << f_value << " | " << setw(15) << F_value << " | " << setw(15) << delta << endl;
    }

    cout << setw(13) << "Таблица 2:" << endl;
    cout << setw(16) << "ε" << " | " << setw(15) << "f(x_ideal)" << " | " << setw(15) << "F(x_ideal)" << " | " << setw(15) << "δ" << endl;

    for (int i = 1; i <= 7; ++i) {
        double current_epsilon = pow(10, -i);
        double f_ideal = f(x_ideal, 50); // Вычисляем значение рядной функции для x_ideal
        double F_ideal = cos(x_ideal) * cos(x_ideal); // Вычисляем значение библиотечной функции для x_ideal
        double delta_ideal = sqrt(fabs(f_ideal * f_ideal - F_ideal)); // Вычисляем невязку для x_ideal
        
        cout << setw(15) << setprecision(7) << current_epsilon << " | " << setw(15) << f_ideal << " | " << setw(15) << F_ideal << " | " << setw(15) << delta_ideal << endl;
    }

    return 0;
}
