/*/
Header de clase Hash Table

Una hash table es una estructura de datos, construida a partir de un arreglo.
Emplea lo que se le conoce como llaves para mapear la posicion de cada elemento colocado.
En esta ocasion se implemento con encadenamiento (a partir de listas enlazadas).
Ocurre un rehashing cada vez que se alcanza un factor de carga de 0.75.

Owen Jauregui Borbon - A01638122
Luis Humberto Sanchez Vaca - A01638029
Samuel Alejandro Diaz del Guante Ochoa - A01637592
/*/

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
