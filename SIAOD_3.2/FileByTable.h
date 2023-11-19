#include "HashTable.h"
#include "BinFile.h"

// получить запись из файла по заданной позиции и вставить в таблицу

int getByPositionAndInsert(HashTable* hashTable, string binfileName, int position) {
	dict_word word;
	if (get_by_position(word, binfileName, position) == 0) {
		insert(hashTable, word.eng_word, position);
		return 0;
	}
	else {
		cout << "Record was not found\n";
		return -1;
	}
}

// удалить запись из файла и из таблицы по ключу

int deleteRecord(HashTable* hashTable, string binfileName, char key[100]) {
	dict_word last_word;
	Element* record_to_delete = search(hashTable, key);
	if (rewrite_by_position(binfileName, record_to_delete->position, last_word) == 0) {

		Element* last_record = search(hashTable, last_word.eng_word);
		if (record_to_delete == nullptr) {
			cout << "Record was not found";
			return -1;
		}
		//нужно заменить позицию последней записи в файле на позицию удаляемой записи
		last_record->position = record_to_delete->position;
		//удалить запись по ключу
		deleteElement(hashTable, key);
		return 0;
	}
	else {
		cout << "Record was not found\n";
		return -1;
	}
}

// найти запись в файле по значению ключа
int findRecordByKey(dict_word& word_to_return, HashTable* hashTable, string binfileName, char key[100]) {

	Element* element = search(hashTable, key);
	if (element == nullptr) {
		cout << "Record was not found\n";
		return -1;
	}
	int position = element->position;

	if (get_by_position(word_to_return, binfileName, position) == 0) {
		return 0;
	}

	return -1;
}


