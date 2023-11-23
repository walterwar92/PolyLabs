#include <iostream>
#include <fstream>
#include <string>
#include <locale>

std::string reverseString(const std::string& str) {
    return std::string(str.rbegin(), str.rend());
}

int main() {
    std::ifstream inputFile("input.txt"); // Имя файла для чтения

    if (!inputFile.is_open()) {
        std::cout << "Unable to open file!" << std::endl;
        return 1;
    }

    std::string word;
    std::locale loc("ru_RU.UTF-8"); // Установка локали для корректной обработки русских букв

    while (inputFile >> word) {
        // Если текущее слово содержит буквы, обрабатываем их
        for (char& c : word) {
            if (std::isalpha(c, loc)) {
                c = std::tolower(c, loc); // Приводим все буквы к нижнему регистру для корректного переворота
            }
        }
        std::cout << reverseString(word) << " ";
    }

    inputFile.close();
    return 0;
}
