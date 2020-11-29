#include "MyHashTable.h"

using namespace std;

MyHashTable::MyHashTable(string archivo){
    this->size=0;
    this->sizeA=389;   // Ajustar tamano inicial si es necesario
    this->tabla=new MyLinkedList[this->sizeA];
    loadData(archivo);
}

// Destructor
// Complejidad: O(1)
MyHashTable::~MyHashTable(){
    // Se libera el e espacio en memoria
    // reservado para el arreglo
    delete [] this->tabla;
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
            put(ip, fecha);
        }
    } else {
        throw invalid_argument("El archivo " + archivo + " no existe");
    }
    data.close();
}

void MyHashTable::rehashing(){
    int tmpSize = this->sizeA;
    this->sizeA = 2 * this->sizeA + 1;
    MyLinkedList* tmp = this->tabla;
    this->tabla = new MyLinkedList[this->sizeA];

    for(int i = 0; i < tmpSize; i++){
        while(!tmp[i].isEmpty()){
            int pos = getPos(tmp[i].getAt(0)->key);
            tabla[pos].insertNode(tmp[i].getAt(0)->key,tmp[i].getAt(0)->date);
            tmp[i].removeFirst();
        }
    }
    delete [] tmp;
}

// Metodo para obtener la posicion de una key
// Recibe el string de la key a convertir
// Se regresa un entero con la posicion
// Complejidad: O(1)
int MyHashTable::getPos(string key){
    // Se hace hash de la key con la funcion
    // ya implementada en c++
    size_t hashT=hash<string>{}(key);
    // Se hace un cast a integer
    int hashCode=static_cast<int>(hashT);
    // Se regresa la posicion valida
    // de acuerdo al tamano del arreglo
    return abs(hashCode)%this->sizeA;
}

// Metodo para insertar un elemento
// Recibe un string con la key(ip) y la fecha del acceso
// No regresa nada
// Complejidad:
//  -Sin rehashing - O(1)
//  -Con rehashing - O(n)
void MyHashTable::put(string key, int date){
    // Se compruba el factor de carga
    if ((float)this->size / this->sizeA >= 0.75){
        rehashing();
    }
    // Se obtiene la posicion de la key
    int pos=getPos(key);
    // Se obtiene el nodo asociado a esa llave
    // si existe
    MyNodoLL* dato = get(key);
    // En caso de existir
    if (dato != nullptr){
        // Se actualiza su informacion
        update(dato, date);
    }
    else{
        // En caso contrario se inserta el nuevo
        // elemento en su lista correspondiente
        this->tabla[pos].insertFirst(key, date);
        // Se aumenta el numero de elementos
        this->size++;
    }
}

// Método auxiliara para actualizar la informacion
// de una ip ya insertada
// Recibe el nodo de la ip asociada y la nueva fecha
// No regresa nada
// Complejidad: O(1)
void MyHashTable::update(MyNodoLL* dato, int date) {
    // Se incrementa el numero de accesos
    dato->access++;
    // Se agrega la nueva fecha
    dato->date.push_back(date);
}

// Metodo para obtener el nodo asociado a una key
// Recibe la key a buscar
// Regresa el nodo correspondiente si se encuentra
// Complejidad: O(1)
MyNodoLL* MyHashTable::get(string key){
    // Se obtiene la posicicon de la key
    int pos=getPos(key);
    // Se obtiene un apuntador a la lista
    // de esa posicion
    MyLinkedList* lista=&this->tabla[pos];
    // Se busca la key y se regresa su nodo
    return lista->getNode(key);
}

void MyHashTable::print(string key)
{
    MyNodoLL* node = get(key);
    if (node != nullptr) {
        cout << "Resumen de IP" << endl;
        cout << "IP: " << node->key << endl;
        cout << "Numero de accesos: " << node->access << endl;
        cout << "Fechas de acceso: ";

        sort(node->date.begin(), node->date.end());

        string meses[] = {"Jan", "Feb", "Mar", "Apr",
                          "May", "Jun", "Jul", "Aug",
                          "Sep", "Oct", "Nov", "Dec"};

        int fecha, mes, dia, hora, minuto;

        for (int i = 0; i < node->date.size(); i++) {
            fecha = node->date[i];
            mes = fecha / 2678400;
            cout << meses[mes - 1] << " ";
            fecha = fecha - mes * 2678400;
            dia = fecha / 86400;
            cout << dia << " ";
            fecha = fecha - dia * 86400;
            hora = fecha / 3600;
            cout << hora << ":";
            fecha = fecha - hora * 3600;
            minuto = fecha / 60;
            if (minuto < 10) {
                cout << "0" << to_string(minuto) << ":";
            } else {
                cout << minuto << ":";
            }
            fecha = fecha - minuto * 60;
            if (fecha < 10) {
                cout << "0" << to_string(fecha);
            } else {
                cout << fecha;
            }
            cout << " | ";
        }
        cout << endl;
    }
    else{
        cout << "No se encontro la IP: " << key << endl;
    }
}

