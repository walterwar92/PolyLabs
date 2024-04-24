#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // Для работы с символами

using namespace std;

// Структура для узла бинарного дерева
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char value) : data(value), left(nullptr), right(nullptr) {}
};

// Функция для построения бинарного дерева из текста
TreeNode* buildBinaryTreeFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return nullptr;
    }

    string line;
    getline(file, line); // Читаем всю строку из файла

    if (line.empty()) {
        cerr << "File is empty." << endl;
        return nullptr;
    }

    // Создаем корень дерева
    TreeNode* root = new TreeNode(line[line.size() - 2]); // Предпоследняя буква

    for (char ch : line) {
        if (isalpha(ch)) { // Проверяем, что символ является буквой
            TreeNode* current = root;
            while (true) {
                if (ch < current->data) {
                    if (current->left == nullptr) {
                        current->left = new TreeNode(ch);
                        break;
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = new TreeNode(ch);
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }
    }

    file.close();
    return root;
}

// Функция для подсчета количества совпадений предпоследней буквы в дереве
int countMatches(TreeNode* root, char target) {
    if (root == nullptr) {
        return 0;
    }

    int count = 0;
    if (root->data == target) {
        count++;
    }
    count += countMatches(root->left, target);
    count += countMatches(root->right, target);

    return count;
}

int main() {
    string filename = "C:/Users/Roman/Desktop/1/42.txt"; // Имя вашего текстового файла
    if (filename.substr(filename.find_last_of(".") + 1) != "txt") {
        cerr << "Invalid file type. Must be a .txt file." << endl;
        return 1;
    }

    TreeNode* root = buildBinaryTreeFromFile(filename);
    if (root == nullptr) {
        cerr << "Failed to build binary tree from file." << endl;
        return 1;
    }

    char target = root->data;
    int matchesCount = countMatches(root, target);

    cout << "Number of matches with the second to last letter '" << target << "': " << matchesCount << endl;

    // Освобождаем память, выделенную под дерево (для полноценного кода нужно добавить деструктор)
    return 0;
}
