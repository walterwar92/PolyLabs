#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

double binom(int n, int k) {
    if (k == 0 || k == n) {
        return 1.0;
    } else {
        return binom(n - 1, k - 1) + binom(n - 1, k);
    }
}

double fact(int n) {
    if (n == 0) {
        return 1.0;
    } else {
        return n * fact(n - 1);
    }
}

double cos2_recursive(int n, double x) {
    return pow(-1, n + 1) * (pow(2, 2 * n - 1) * pow(x, 2 * n)) / fact(2 * n);
}

double cos2_series(double x, double E) {
    double result = 1.0;
    double term = 1.0;
    int n = 1;

    do {
        term = cos2_recursive(n, x);
        result -= term;
        n++;
    } while (fabs(term) > E);

    return result;
}

int main() {
    double E, x_start, x_end, dx, x_ideal;
    string NewStr = "0";
    int count = 0;
    do {
        cout << "Введите точность E (от 10^-7 до 10^-1): ";
        cin >> E;
        if (cin.fail() || E < 1e-7 || E > 0.1) {
            cout << "Пожалуйста, введите корректное значение для точности E (от 10^-7 до 10^-1)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (E < 1e-7 || E > 0.1);

    do {
        cout << "Введите границы промежутка вычисления x_start и x_end:";
        cin >> x_start >> x_end;
        if (cin.fail() || x_start >= x_end) {
            cout << "Пожалуйста, введите корректные значения границ промежутка x_start и x_end (x_start должен быть меньше x_end)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (x_start >= x_end);

    do {
        cout << "Введите шаг dx:";
        cin >> dx;
        if (cin.fail() || dx <= 0) {
            cout << "Пожалуйста, введите корректное положительное число для шага dx." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (dx <= 0);

    do {
        cout << "Введите значение x_ideal для точного расчёта:";
        cin >> x_ideal;
        if (cin.fail()) {
            cout << "Пожалуйста, введите числовое значение для x_ideal." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (cin.fail());

    cout << left << setw(12) << "| x" << "| f(x)" << "    | F(x)" << "    | delta     |" << endl;
    cout << setw(45) << setfill('-') << "" << setfill(' ') << endl;

    for (double x = x_start; x <= x_end; x += dx) {
        double f_x = cos2_series(x, E);
        double F_x = cos(x) * cos(x);
        double delta = sqrt(fabs(f_x * f_x - F_x * F_x)) - 1.0;

        cout << left << setw(12) << "| " + to_string(x).substr(0, 6) << "| " + to_string(f_x).substr(0, 10) << "| " + to_string(F_x).substr(0, 10) << "| " + to_string(delta).substr(0, 10) << " |" << endl;
    }

    cout << left << setw(12) << "| E" << "| f(x_i)  " << "| F(x_i)  " << "| delta     |" << endl;
    cout << setw(45) << setfill('-') << "" << setfill(' ') << endl;

    for (double current_E = 0.1; current_E >= 1e-7; current_E *= 0.1) {
        count++;
        double f_x_ideal = cos2_series(x_ideal, current_E);
        double F_x_ideal = cos(x_ideal) * cos(x_ideal);
        double delta_ideal = sqrt(fabs(f_x_ideal * f_x_ideal - F_x_ideal * F_x_ideal)) - 1.0;

        cout << left << setw(12) << "| " + to_string(current_E).substr(0, 13) + NewStr << "| " + to_string(f_x_ideal).substr(0, 10) << "| " + to_string(F_x_ideal).substr(0, 10) << "| " + to_string(delta_ideal).substr(0, 10) << " |" << endl;
        if (count == 6)
            NewStr = "1";

    }

    return 0;
}
