#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

bool isTxtFile(const string& filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos == string::npos) {
        return false;
    }
    string extension = filename.substr(dotPos + 1);
    return (extension == "txt");
}

int main() {
    string filePath;
    cout << "Введите путь к файлу: ";
    cin >> filePath;

    if (!isTxtFile(filePath)) {
        cout << "Файл не является текстовым файлом (.txt).\n";
        return 1;
    }

    wifstream inputFile(filePath);
    inputFile.imbue(locale(""));

    if (!inputFile.is_open()) {
        cout << "Не удалось открыть файл.\n";
        return 1;
    }

    wstring word;
    while (inputFile >> word) {
        wcout << wstring(word.rbegin(), word.rend()) << L" ";
    }

    inputFile.close();

    return 0;
}
