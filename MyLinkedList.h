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
