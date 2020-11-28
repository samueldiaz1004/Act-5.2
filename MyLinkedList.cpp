#include "MyLinkedList.h"

using namespace std;

MyLinkedList::MyLinkedList(){
    this->head=this->tail=nullptr;
    this->size=0;
}

MyLinkedList::~MyLinkedList(){
}

int MyLinkedList::length(){
    return this->size;
}

bool MyLinkedList::isEmpty(){
    return this->size==0;
}

int MyLinkedList::getAt(string key){
    MyNodoLL* current=this->head;
    for(int i=0;i<this->size;i++){
        if(current->key==key){
            return current->access;
        }
        current=current->next;
    }
    throw invalid_argument("No se encontró "+key+" en la lista");
}

MyNodoLL* MyLinkedList::getAt(int pos){
    if(pos>=0 && pos<this->size){
        MyNodoLL* current=this->head;
        for(int i=0;i<pos;i++){
            current=current->next;
        }
        return current;
    }else{
        throw invalid_argument("No se puede insertar en la posición "+to_string(pos)+" en una lista de tamaño "+to_string(this->size));
    }
}

void MyLinkedList::insertFirst(string key, int date){
    this->head=new MyNodoLL(key,date,this->head);
    if(this->tail==nullptr){
        this->tail=this->head;
    }
    this->size++;
}

void MyLinkedList::removeFirst(){
    if(this->size>0){
        MyNodoLL* tmp=this->head;
        this->head=this->head->next;
        this->size--;
        if(this->size==0){
            this->tail=nullptr;
        }
        delete tmp;
    }else{
        throw invalid_argument("No se puede borrar el inicio de una lista vacía");
    }
}

MyNodoLL* MyLinkedList::getNode(string key)
{
    MyNodoLL* current = this->head;
    while(current->key != key && current != nullptr){
        current = current->next;
    }
    if(current->key == key){
        return current;
    }
    else{
        throw invalid_argument("No se puedo encontrar "+key+" en los registros");
    }
}
