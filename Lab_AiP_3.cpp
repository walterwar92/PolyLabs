#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

// Функция, которая переворачивает строку
string reverseString(const string& str) {
    return string(str.rbegin(), str.rend());
}

int main() {
    ifstream inputFile("input.txt"); // Имя файла для чтения

    if (!inputFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    string word;
    locale loc("ru_RU.UTF-8"); // Установка локали для корректной обработки русских букв

    while (inputFile >> word) {
        // Если текущее слово содержит буквы, обрабатываем их
        for (char& c : word) {
            if (isalpha(c, loc)) {
                c = tolower(c, loc); // Приводим все буквы к нижнему регистру для корректного переворота
            }
        }
        cout << reverseString(word) << " ";
    }

    inputFile.close();
    return 0;
}
