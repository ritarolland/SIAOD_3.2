#define _HAS_STD_BYTE 0
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;


struct dict_word {
    char eng_word[100] = {};
    char rus_word[100] = {};
    dict_word() {}
    dict_word(char eng_word[100], char rus_word[100]) {
        strcpy_s(this->eng_word, eng_word);
        strcpy_s(this->rus_word, rus_word);
    }
};

int write_in_binfile(string filename_text, string filename_bin) {
    ifstream fin(filename_text);
    ofstream fout(filename_bin, ios::binary);
    if (!fin.is_open() || !fout.is_open()) {
        cout << "Can not open the file\n";
        return -1; //Код ошибки
    }

    char eng_word[100];
    char rus_word[100];

    while (!fin.eof()) {
        fin >> eng_word;
        fin >> rus_word;
        dict_word new_word(eng_word, rus_word);
        fout.write(reinterpret_cast<char*>(&new_word), sizeof(dict_word));
    }

    fin.close();
    fout.close();
    return 0;
}

int read_from_binfile(string filename_bin) {
    ifstream fin(filename_bin, ios::binary);
    if (!fin.is_open()) {
        cout << "Can not open the file\n";
        return -1;
    }

    dict_word word;
    while (fin.read(reinterpret_cast<char*>(&word), sizeof(dict_word))) {
        cout << word.eng_word << " " << word.rus_word << "\n";
    }


    fin.close();
    return 0;
}

int bin_to_txt(string filename_bin, string filename_txt) {
    ifstream fin(filename_bin, ios::binary);
    ofstream fout(filename_txt);
    if (!fin.is_open() || !fout.is_open()) {
        cout << "Can not open the file\n";
        return -1;
    }

    dict_word word;
    while (fin.read(reinterpret_cast<char*>(&word), sizeof(dict_word))) {
        fout << word.eng_word << " " << word.rus_word << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}

int get_by_position(dict_word& word_to_return, string filename_bin, int pos) {
    ifstream fin(filename_bin, ios::binary);
    if (!fin.is_open()) {
        cout << "Can not open the file\n";
        return -1;
    }

    fin.seekg(0, ios::end);
    int max_pos = fin.tellg() / sizeof(dict_word);
    if (pos > max_pos || pos < 1) {
        cout << "Wrong position\n";
        return -1;
    }
    int recordPos = (pos - 1) * sizeof(dict_word);
    fin.seekg(recordPos, ios::beg);
    dict_word word;
    fin.read(reinterpret_cast<char*>(&word), sizeof(dict_word));
    word_to_return = word;

    fin.close();
    return 0;

}

int rewrite_by_key(string filename_bin, string key) {
    fstream file(filename_bin, ios::binary | ios::out | ios::in);
    if (!file.is_open()) {
        cout << "Can not open the file\n";
        return -1;
    }
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    int numRecords = fileSize / sizeof(dict_word);
    int recordPos = -1; // Позиция записи для удаления
    file.seekg(0, std::ios::beg);
    for (int i = 0; i < numRecords; ++i) {
        dict_word word;
        file.read(reinterpret_cast<char*>(&word), sizeof(dict_word));
        if (word.eng_word == key) {
            recordPos = i;
            break;
        }
    }
    if (recordPos != -1) {
        int WORD_SIZE = sizeof(dict_word);
        file.seekg(-WORD_SIZE, std::ios::end);
        dict_word last_word;
        file.read(reinterpret_cast<char*>(&last_word), sizeof(dict_word));
        file.seekp(recordPos * sizeof(dict_word), std::ios::beg);
        file.write(reinterpret_cast<const char*>(&last_word), sizeof(dict_word));
        int recordSize = sizeof(dict_word);
        int newFileSize = fileSize - recordSize;
        fs::resize_file(filename_bin, newFileSize);
    }
    else {
        cout << "No such word in the file\n";
        return -1;
    }
    file.close();
    return 0;
}


int print_words(char letter, string filename_bin) {
    ifstream fin(filename_bin, ios::binary);
    if (!fin.is_open()) {
        cout << "Can not open the file\n";
        return -1;
    }

    dict_word word;
    while (fin.read(reinterpret_cast<char*>(&word), sizeof(dict_word))) {
        if (word.eng_word[0] == letter) {
            cout << word.eng_word << " " << word.rus_word << "\n";
        }
    }

    fin.close();
    return 0;
}

int change_translation(string filename_bin, char key[100], char new_translation[100]) {
    fstream file(filename_bin, ios::binary | ios::out | ios::in);
    if (!file.is_open()) {
        cout << "Can not open the file\n";
        return -1;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    int numRecords = fileSize / sizeof(dict_word);
    int recordPos = -1; // Позиция записи для изменения

    file.seekg(0, std::ios::beg);
    for (int i = 0; i < numRecords; ++i) {
        dict_word word;
        file.read(reinterpret_cast<char*>(&word), sizeof(dict_word));
        if (word.eng_word == key) {
            recordPos = i;
            break;
        }
    }
    if (recordPos != -1) {
        dict_word new_word(key, new_translation);
        file.seekp(recordPos * sizeof(dict_word), std::ios::beg);
        file.write(reinterpret_cast<const char*>(&new_word), sizeof(dict_word));

    }
    else {
        cout << "No such word in the file\n";
        return -1;
    }

    file.close();
    return 0;
}


