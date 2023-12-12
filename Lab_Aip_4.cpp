#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <cctype>

using namespace std;

const int MAX_SIZE = 30;

void fillMatrix(int matrix[][MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 20 + 1;
        }
    }
}

void printRedMatrix(int matrix[][MAX_SIZE], int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void printBlueMatrix(int matrix[][MAX_SIZE], int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void transformMatrix(int matrix[][MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (j < i) {
                matrix[i][j] = 0;
            }
        }
    }
}
int main() {
    int size;
    string input;
    cout << "Введите размерность квадратной матрицы:";
    cin >> input;

    bool isNumber = true;
    for (char c : input) {
        if (!isdigit(c)) {
            isNumber = false;
            break;
        }
    }

    if (!isNumber || (isNumber && (stoi(input) <= 0 || stoi(input) > MAX_SIZE))) {
        cout << "Размер должен быть положительным числом и не превышать " << MAX_SIZE << ", а также не быть числом" << "." << endl;
        return 1;
    }

    size = stoi(input);

    int matrix[MAX_SIZE][MAX_SIZE];

    srand(static_cast<unsigned int>(time(0)));

    fillMatrix(matrix, size);

    cout << "Исходная матрица:" << endl;
    printRedMatrix(matrix, size);
    fillMatrix(matrix, size);
    transformMatrix(matrix, size);
    cout << "Преобразованная матрица:" << endl;
    printBlueMatrix(matrix, size);
    return 0;
}
