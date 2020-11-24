#include "MyHashTable.h"

using namespace std;

MyHashTable::MyHashTable(string archivo){
    this->size=0;
    this->sizeA=11;
    this->tabla=new MyLinkedList[this->sizeA];
}

MyHashTable::~MyHashTable(){

}

void MyHashTable::rehashing(){

}

int MyHashTable::getPos(string key){
    size_t hashT=hash<string>{}(key);
    int hashCode=static_cast<int>(hashT);
    return abs(hashCode)%this->sizeA;
}

void MyHashTable::put(string key, int value, vector<string> fecha){
    int pos=getPos(key);
    this->tabla[pos].insertFirst(key,value,fecha);
    this->size++;
}


int MyHashTable::get(string key){
    int pos=getPos(key);
    MyLinkedList* lista=&this->tabla[pos];
    return lista->getAt(key);
}

void MyHashTable::print(string key)
{

}
