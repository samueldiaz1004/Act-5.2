/*/
Header de clase Linked List

Estructura de datos complementaria a la implementacion de la clase Hash Table
Es una collecion linear de datos almacenados en nodos que siguen una secuencia
determinada a partir de apuntadores.

Owen Jauregui Borbon - A01638122
Luis Humberto Sanchez Vaca - A01638029
Samuel Alejandro Diaz del Guante Ochoa - A01637592
/*/

#ifndef MY_LINKEDLIST_H
#define MY_LINKEDLIST_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct MyNodoLL{
    string key;                 // direccion ip
    int access;                 // num de accesos
    vector<int> date;        // lista de fechas
    MyNodoLL* next;

    MyNodoLL(string key, int date, MyNodoLL* next){
        this->key = key;
        this->access = 1;
        this->date.push_back(date);
        this->next = next;
    }

    MyNodoLL(string key, int date):MyNodoLL(key, date, nullptr){}

    MyNodoLL(string key, vector<int> date, MyNodoLL* next){
        this->key = key;
        this->access = date.size();
        this->date = date;
        this->next = next;
    }
};

class MyLinkedList{
    private:
        MyNodoLL* head;
        MyNodoLL* tail;
        int size;
    public:
        MyLinkedList();
        ~MyLinkedList();
        int length();
        bool isEmpty();
        MyNodoLL* getAt(int pos);
        int getAt(string key);
        void insertFirst(string key, int date);
        void insertNode(string key, vector<int> date);
        void removeFirst();
        MyNodoLL* getNode(string key);
};
#endif
