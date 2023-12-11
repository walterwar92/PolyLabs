#include <iostream>
#include <cstdlib> // Для функции rand()
#include <ctime>   // Для функции time()
#include <windows.h>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 30; // Максимальный размер матрицы

void fillMatrix(int matrix[][MAX_SIZE], int size) {
    // Заполнение матрицы случайными числами от 1 до 10
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
    // Приведение матрицы к нужному виду
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (j < i) {
                matrix[i][j] = 0; // Обнуляем элементы ниже главной диагонали
            }
        }
    }
}
int main() {
    int size;
    cout << "Введите размерность квадратной матрицы: ";
    cin >> size;

    if (size <= 0 || size > MAX_SIZE) {
        cout << "Размер должен быть положительным и не превышать " << MAX_SIZE << "." << endl;
        return 1;
    }

    int matrix[MAX_SIZE][MAX_SIZE];

    // Инициализация генератора случайных чисел
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
