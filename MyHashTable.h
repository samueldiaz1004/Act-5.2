#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include <iostream>
#include <string>
#include <functional>
#include <cmath>
#include "MyLinkedList.h"

class MyHashTable{
    private:
        int size;//El número de elementos que tiene almacenado
        int sizeA; //El tamaño del arreglo
        MyLinkedList* tabla;
        void rehashing();
        int getPos(string key);
        void put(string key, int date);
        int get(string key);
        void update(int date);

    public:
        MyHashTable(string archivo);
        ~MyHashTable();
        void print(string key);
};
#endif
