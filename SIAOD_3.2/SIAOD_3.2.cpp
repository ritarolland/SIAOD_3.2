// SIAOD_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//#include "HashTableManagement.h"
#include "BinFile.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    //HashTable* hashTable = new HashTable(11);
    //char eng_word[100];
    ///*strcpy_s(eng_word, "friend");

    //cout << hashTable->hashFunction(eng_word);*/


    //strcpy_s(eng_word, "pillow");
    //char rus_word[100] = "подушка";

    //insert(hashTable, eng_word, rus_word);
    //strcpy_s(eng_word, "phone");
    //strcpy_s(rus_word, "телефон");
    //insert(hashTable, eng_word, rus_word);
    //strcpy_s(eng_word, "friend");
    //strcpy_s(rus_word, "друг");
    //insert(hashTable, eng_word, rus_word);
    //hashTable->print();
    //dict_word* word = search(hashTable, eng_word);
    //if(word != nullptr) cout << word->rus_word;
    //strcpy_s(eng_word, "phone");
    //deleteElement(hashTable, eng_word);
    //cout << endl;
    //hashTable->print();

    string FILENAME_TEXT1;
    string FILENAME_BIN1;
    int command = 1;
    int pos;
    char key[100];
    char new_translation[100];
    dict_word word;
    dict_word& word_link = word;
    while (command != -1) {
        cout << "Введите 1, чтобы преобразовать тестовые данные из текстового файла в двоичный файл" <<
            "\nВведите 2, чтобы сохранить данные двоичного файла в текстовом" <<
            "\nВведите 3, чтобы вывести все записи двоичного файла" <<
            "\nВведите 4, чтобы получить доступ к записи по ее порядковому номеру в файле" <<
            "\nВведите 5, чтобы выполнить удаление записи с заданным значением ключа путем замены на последнюю запись" <<
            "\nВведите 6, чтобы сформировать список английских слов, начинающихся с указанной буквы и их русский перевод" <<
            "\nВведите 7, чтобы обновить запись, записав новый вариант русского перевода по заданному слову" <<
            "\nВведите -1, чтобы завершить работу программы\n";
        cin >> command;
        switch (command) {
        case 1:
            cout << "Введите имя текстового файла\n";
            cin >> FILENAME_TEXT1;
            cout << "Введите имя бинарного файла\n";
            cin >> FILENAME_BIN1;
            if (write_in_binfile(FILENAME_TEXT1, FILENAME_BIN1) == 0) cout << "Успех!\n";
            break;
        case 2:
            cout << "Введите имя бинарного файла\n";
            cin >> FILENAME_BIN1;
            cout << "Введите имя текстового файла\n";
            cin >> FILENAME_TEXT1;
            if (bin_to_txt(FILENAME_BIN1, FILENAME_TEXT1) == 0) cout << "Успех!\n";
            break;
        case 3:
            cout << "Введите имя бинарного файла\n";
            cin >> FILENAME_BIN1;
            read_from_binfile(FILENAME_BIN1);
            break;
        case 4:
            cout << "Введите имя бинарного файла\n";
            cin >> FILENAME_BIN1;
            cout << "Введите порядковый номер записи\n";
            cin >> pos;

            if (get_by_position(word_link, FILENAME_BIN1, pos) == 0) {
                cout << "Полученное слово: " << word.eng_word << " " << word.rus_word << endl;
            };
            break;
        case 5:
            cout << "Введите имя бинарного файла\n";
            cin >> FILENAME_BIN1;
            cout << "Введите слово, которое хотите удалить\n";
            cin >> key;
            if (rewrite_by_key(FILENAME_BIN1, key) == 0) cout << "Успех!\n";
            break;
        case 6:
            cout << "Введите имя бинарного файла\n";
            cin >> FILENAME_BIN1;
            char letter;
            cout << "Введите букву\n";
            cin >> letter;
            print_words(letter, FILENAME_BIN1);
            break;
        case 7:
            cout << "Введите имя бинарного файла\n";
            cin >> FILENAME_BIN1;
            cout << "Введите слово и его новый перевод через пробел\n";
            cin >> key;
            cin >> new_translation;
            change_translation(FILENAME_BIN1, key, new_translation);
            break;
        case -1:
            break;
        default:
            cout << "Команда введена неверно\n";
            break;
        }
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
