#ifndef MY_LINKEDLIST_H
#define MY_LINKEDLIST_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct MyNodoLL{
    string key;                 // direccion ip
    int access;                 // num de accesos
    vector<string> date;        // lista de fechas
    MyNodoLL* next;

    MyNodoLL(string key, int access, vector<string> date, MyNodoLL* next){
        this->key = key;
        this->access = access;
        this->date = date;
        this->next = next;
    }

    MyNodoLL(string key,int access, vector<string> date):MyNodoLL(key, access, date, nullptr){}
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
        int getAt(string key); // regresa num de accesos
        void insertFirst(string key, int access, vector<string> date);
        void removeFirst();
        /*/
        friend ostream& operator<<(ostream& os,const MyLinkedList& ll){
            MyNodoLL* current=ll.head;
            for(int i=0;i<ll.size;i++){
                os<<"["<<current->key<<",";
                os<<current->data<<"]";
                current=current->next;
            }
            return os;
        }
        /*/
};
#endif
