#include <iostream>
#include <map>
#include <fstream>
#include <string>
using namespace std;

class Dictionary {
private:
     map< string,  string> dictionary;

public:
    // Метод для добавления слова в словарь
    void addWord(string word, string translation) {
        dictionary[word] = translation;
    }


     string findWord(string word) {
        if (dictionary.count(word) > 0) {
            return dictionary[word];
        }
        else {
            return "Слово не найдено.";
        }
    }


    void removeWord(string word) {
        dictionary.erase(word);
    }

    void editWord(string word,string newTranslation) {
        if (dictionary.count(word) > 0) {
            dictionary[word] = newTranslation;
        }
    }


    void loadFromFile(string filename) {
        ifstream inputFile;
        inputFile.open(filename);
        if (inputFile.is_open()) {
            dictionary.clear(); // Очищаем текущий словарь

             string line="";
            while (getline(inputFile, line)) {
                    string word = "";
                    string translation = "";
                    int iter = 0;
                    for (int iter = 0; iter < line.length(); iter++) {
                        if (line[iter] == ':') break;
                        else word += line[iter];
                    }
                    for (int iter = 0; iter < line.length(); iter++) {
                        translation += line[iter];
                    }
                    dictionary[word] = translation;
                
            }

            inputFile.close();
             cout << "Словарь загружен из файла." <<  endl;
        }
        else {
             cout << "Не удалось открыть файл." <<  endl;
        }
    }


    void saveToFile(string filename) {
         ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (auto& entry : dictionary) {
                outputFile << entry.first << ":" << entry.second <<  endl;
            }

            outputFile.close();
             cout << "Словарь записан в файл." <<  endl;
        }
        else {
             cout << "Не удалось открыть файл." <<  endl;
        }
    }
    void show() {
        for (auto& entry : dictionary) {
            cout << entry.first << ": " << entry.second << endl;
            //не понимаю почему выводится 2 раза first
           
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    Dictionary dictionary;

    // Добавление слов в словарь
    dictionary.addWord("apple", "яблоко");
    dictionary.addWord("banana", "банан");
    dictionary.addWord("orange", "апельсин");

    // Поиск и вывод значения по ключу
     string translation = dictionary.findWord("apple");
     cout << "Перевод слова 'apple': " << translation <<  endl;

    // Редактирование значения по ключу
    dictionary.editWord("banana", "банановый");



    // Запись словаря в файл
    dictionary.saveToFile("dictionary.txt");

    // Чтение словаря из файла
    dictionary.loadFromFile("dictionary.txt");

    // Поиск и вывод значения по ключу после загрузки из файла
    translation = dictionary.findWord("apple");
     cout << "Перевод слова 'apple' после загрузки из файла: " << translation <<  endl;
     cout << "вывод всего словаря" << endl;
     dictionary.show();
     // Удаление элемента по ключу
     cout << "Удаление слова orange" << endl;
     dictionary.removeWord("orange");
     cout << "вывод всего словаря"<<endl;
     dictionary.show();

    return 0;
}