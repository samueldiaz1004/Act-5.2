#include "MyHashTable.h"

using namespace std;

MyHashTable::MyHashTable(string archivo){
    this->size=0;
    this->sizeA=4027;   // Ajustar tama�o inicial si es necesario
    this->tabla=new MyLinkedList[this->sizeA];
    loadData(archivo);
}

MyHashTable::~MyHashTable(){

}

void MyHashTable::loadData(string archivo){
    ifstream data;
    string elemento = "", ip, temp = "", linea_;
    stringstream aux, linea;
    int cont_palabra = 0, factorTemp;
    int fecha;
    string meses[] = {"Jan", "Feb", "Mar", "Apr",
                      "May", "Jun", "Jul", "Aug",
                      "Sep", "Oct", "Nov", "Dec"};

    data.open(archivo.c_str());
    if (data.is_open()) {
        while(getline(data, linea_)) {
            linea.str(linea_);
            while(cont_palabra < 4) {
                linea >> elemento;
                if (cont_palabra == 0) {
                    for(int i = 0; i < 12; i++){
                        if(elemento == meses[i]){
                            fecha = (i+1)*2678400;
                        }
                    }
                } else if (cont_palabra == 1) {
                    fecha += stoi(elemento)*86400;
                } else if (cont_palabra == 2) {
                    factorTemp = 3600;
                    for(int i = 0; i < elemento.size(); i++) {
                        if(elemento[i] != ':' && i < elemento.size()) {
                            temp += elemento[i];
                        } else {
                            fecha += stoi(temp)*factorTemp;
                            factorTemp = factorTemp/60;
                            temp = "";
                        }
                    }
                    fecha += stoi(temp)*factorTemp;
                    temp = "";
                } else if (cont_palabra == 3) {
                    int i = 0;
                    ip = "";
                    while(elemento[i] != ':') {
                        ip += elemento[i];
                        i++;
                    }
                }
                cont_palabra++;
            }
            cont_palabra = 0;
            //cout << fecha << endl;
            put(ip, fecha);
        }
    } else {
        throw invalid_argument("El archivo "+archivo+" no existe");
    }
}

void MyHashTable::rehashing(){

}

int MyHashTable::getPos(string key){
    size_t hashT=hash<string>{}(key);
    int hashCode=static_cast<int>(hashT);
    return abs(hashCode)%this->sizeA;
}

void MyHashTable::put(string key, int date){
    int pos=getPos(key);
    this->tabla[pos].insertFirst(key,date);
    this->size++;
}


MyNodoLL* MyHashTable::get(string key){
    int pos=getPos(key);
    MyLinkedList* lista=&this->tabla[pos];
    return lista->getNode(key);
}

void MyHashTable::print(string key)
{
    MyNodoLL* node = get(key);
    cout << "Resumen de IP" << endl;
    cout << "IP: " << node->key << endl;
    cout << "Numero de accesos: " << node->access << endl;
    cout << "Fechas de acceso: ";

    sort(node->date.begin(),node->date.end());

    string meses[] = {"Jan", "Feb", "Mar", "Apr",
                    "May", "Jun", "Jul", "Aug",
                    "Sep", "Oct", "Nov", "Dec"};

    int fecha, mes, dia, hora, minuto;

    for(int i = 0; i < node->date.size(); i++){
        fecha = node->date[i];
        mes = fecha / 2678400;
        cout << meses[mes-1] << " ";
        fecha = fecha - mes*2678400;
        dia = fecha/86400;
        cout << dia << " ";
        fecha = fecha - dia*86400;
        hora = fecha / 3600;
        cout << hora << ":";
        fecha = fecha - hora*3600;
        minuto = fecha / 60;
        if(minuto < 10){
            cout << "0" << to_string(minuto) << ":";
        }
        else{
            cout << minuto << ":";
        }
        fecha = fecha - minuto*60;
        if(fecha < 10){
            cout << "0" << to_string(fecha);
        }
        else{
            cout << fecha;
        }
        cout << " | ";
    }
    cout << endl;
}

void MyHashTable::update(int date)
{

}
