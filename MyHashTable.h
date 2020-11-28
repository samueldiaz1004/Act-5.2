#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include <cmath>
#include <algorithm>
#include "MyLinkedList.h"

class MyHashTable{
    private:
        int size;//El número de elementos que tiene almacenado
        int sizeA; //El tamaño del arreglo
        MyLinkedList* tabla;
        void loadData(string archivo);
        void rehashing();
        int getPos(string key);
        void put(string key, int date);
        MyNodoLL* get(string key);
        void update(MyNodoLL* dato, int date);

    public:
        MyHashTable(string archivo);
        ~MyHashTable();
        void print(string key);
};
#endif
