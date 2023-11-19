#include <iostream>
#include <vector>
#include <cstring>


using namespace std;

struct Element {
    int position;
    char eng_word[100];
    Element() {}
    Element(char eng_word[100], int position) {
        strcpy_s(this->eng_word, eng_word);
        this->position = position;
    }
};

struct HashTable {
    int capacity;
    int size;
    Element** tableElements;

    HashTable(int capacity);
    ~HashTable();
    int hashFunction(char key[100]);
};

int HashTable::hashFunction(char key[100]) {
    int hash = 0;
    for (int i = 0; i < 100; i++) {
        hash = hash + key[i];
    }
    hash = hash % capacity;
    return hash;
}

HashTable::~HashTable() {
    delete[] tableElements;
}

HashTable::HashTable(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->tableElements = new Element * [capacity];
    for (int i = 0; i < capacity; i++) {
        tableElements[i] = nullptr;
    }
}

void print(HashTable hashTable) {
    for (int i = 0; i < hashTable.capacity; i++) {
        if (hashTable.tableElements[i] != nullptr) {
            cout << hashTable.tableElements[i]->eng_word << " " << hashTable.tableElements[i]->position << endl;
        }
    }
}

void insert(HashTable*, char[100], int);

void rehash(HashTable* hashTable) {

    HashTable* newTable = new HashTable(hashTable->capacity * 2);
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->tableElements[i] != nullptr) {
            insert(newTable, hashTable->tableElements[i]->eng_word, hashTable->tableElements[i]->position);
        }
    }
    delete hashTable;
    *hashTable = *newTable;

}


void insert(HashTable* hashTable, char eng_word[100], int position) {
    if (hashTable->capacity == hashTable->size) {
        rehash(hashTable);
    }
    int index = hashTable->hashFunction(eng_word);
    while (hashTable->tableElements[index] != nullptr) {
        index = (index + 1) % hashTable->capacity;
    }
    hashTable->tableElements[index] = new Element(eng_word, position);
    hashTable->size++;
}

Element* search(HashTable* hashTable, char eng_word[100]) {
    int index = hashTable->hashFunction(eng_word);

    for (int iterations = 0; iterations < hashTable->capacity; iterations++) {
        if (hashTable->tableElements[index] != nullptr && strcmp(hashTable->tableElements[index]->eng_word, eng_word) == 0) {
            return hashTable->tableElements[index];
        }
        index = (index + 1) % hashTable->capacity;
    }
    return nullptr;

}

void deleteElement(HashTable* hashTable, char eng_word[100]) {

    int index = hashTable->hashFunction(eng_word);

    for (int iterations = 0; iterations < hashTable->capacity; iterations++) {
        if (hashTable->tableElements[index] != nullptr && strcmp(hashTable->tableElements[index]->eng_word, eng_word) == 0) {
            delete hashTable->tableElements[index];
            hashTable->tableElements[index] = nullptr;
            hashTable->size--;
            return;
        }
        index = (index + 1) % hashTable->capacity;
    }

}

