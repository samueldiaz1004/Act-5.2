/*/
Implementacion de clase Hash Table

Owen Jauregui Borbon - A01638122
Luis Humberto Sanchez Vaca - A01638029
Samuel Alejandro Diaz del Guante Ochoa - A01637592
/*/

#include "MyHashTable.h"

using namespace std;

// Constructor
// Complejidad: O(n)
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

// Metodo para extraer e insertar la informacion 
// de los elementos desde un archivo .txt
// Recibe un string con el nombre del archivo
// del que se van a extraer los elementos
// No se regresa ningun valor
// Complejidad: O(n)
void MyHashTable::loadData(string archivo){
    ifstream data; // Archivo de entrada
    // Strings para la separacion de datos
    string elemento = "", ip, temp = "", linea_;
    // Stream de string para poder separar datos
    // de manera sencilla
    stringstream aux, linea; 
    int cont_palabra = 0, factorTemp; // Contadores aux
    int fecha; // Fecha en formato para ordenamiento
    // Arreglo con los nombres de los meses para 
    // transformarlos a int
    string meses[] = {"Jan", "Feb", "Mar", "Apr",
                      "May", "Jun", "Jul", "Aug",
                      "Sep", "Oct", "Nov", "Dec"};

    // Inicio de lectura del archivo
    data.open(archivo.c_str());
    if (data.is_open()) {
        // Lectura de cada linea
        while(getline(data, linea_)) {
            linea.str(linea_);
            // Ciclo para extraer los primeros 4 datos separados
            // por caracteres de espacio
            while(cont_palabra < 4) {
                // Extraccion del cada dato separado por coma
                linea >> elemento;

                // Condicionales para separar los datos del formato
                if (cont_palabra == 0) {
                    // Ciclo para saber el numero del mes dado
                    for(int i = 0; i < 12; i++){
                        if(elemento == meses[i]){
                            // Se asigna el mes en formato a la fecha
                            fecha = (i+1)*2678400;
                        }
                    }
                } else if (cont_palabra == 1) {
                    // Se añade el dia en formato a la fecha
                    fecha += stoi(elemento)*86400;
                } else if (cont_palabra == 2) {
                    // Se extrae la hora, los minutos y los seguntos
                    // y se le asignan a la fehca en formato
                    factorTemp = 3600;
                    for(int i = 0; i < elemento.size(); i++) {
                        //Se separa la hora mediante el caracter ':'
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
                    // Se extrae la ip hasta encontrar el inicio del puerto
                    while(elemento[i] != ':') {
                        ip += elemento[i];
                        i++;
                    }
                }
                cont_palabra++;
            }
            cont_palabra = 0;
            // Se agrega el elemento con la ip y la fecha en formato
            put(ip, fecha);
        }
    } else {
        // En caso de no encontrar el archivo, se arroja una excepcion
        throw invalid_argument("El archivo " + archivo + " no existe");
    }
    // Se cierra el archivo
    data.close();
}

// Metodo para aumentar el tamano de la tabla y redistribuir nodos
// Esto ocurre cuando el factor de carga alcanza o pasa un 0.75
// Se amplia tabla por el doble mas uno y se vuelven a insertar
// todos los nodos de acuerdo al nuevo codigo hash
// No recibe ni regresa algun valor
// Complejidad computacional: O(n)
void MyHashTable::rehashing(){
    // Crear un arreglo temporal para guardar los datos ya insertados
    int tmpSize = this->sizeA;
    this->sizeA = 2 * this->sizeA + 1;
    // Vaciar los contenidos del arreglo viejo al temporal y aumentar tama�o de la tabla
    MyLinkedList* tmp = this->tabla;
    this->tabla = new MyLinkedList[this->sizeA];
    // Recorrer tabla
    for(int i = 0; i < tmpSize; i++){
        // Por cada nodo visitado:
        while(!tmp[i].isEmpty()){
            // Obtenr codigo hash adaptado al nuevo tama�o de la tabla
            int pos = getPos(tmp[i].getAt(0)->key);
            // Colocar nodo en la tabla nueva
            tabla[pos].insertNode(tmp[i].getAt(0)->key,tmp[i].getAt(0)->date);
            // Borrar nodo antiguo
            tmp[i].removeFirst();
        }
    }
    // Borrar arreglo con informacion vieja para evitar memory leaks
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

// Metodo auxiliar para actualizar la informacion
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

// Metodo para despliegar informacion de la Ip seleccionada
// Recibe como parametro la Ip sin la informacion del puerto
// No regresa algun valor
// Complejidad computacional: O(n)
void MyHashTable::print(string key)
{
    // Obtener nodo para acceder a toda su informacion
    MyNodoLL* node = get(key);
    // Revisar que si exista en los registros de la tabla
    if (node != nullptr) {
        // Imprimir a pantalla informacion de la ip seleccionada
        cout << "Resumen de IP" << endl;
        cout << "IP: " << node->key << endl;
        cout << "Numero de accesos: " << node->access << endl;
        cout << "Fechas de acceso: ";
        // Acomodar las fechas de acceso de forma ascendete
        sort(node->date.begin(), node->date.end());
        // Arreglo de referencia para convertir valor numericos de las fechas
        // a un formato de caracteres
        string meses[] = {"Jan", "Feb", "Mar", "Apr",
                          "May", "Jun", "Jul", "Aug",
                          "Sep", "Oct", "Nov", "Dec"};
        int fecha, mes, dia, hora, minuto;
        // Formato de impresion de las fechas
        // Ej: [mes] [dia] [hora]:[minutos][segundos] | [mes] [dia] ...
        // Ej: Oct 9 3:10:23 | Oct 10 10:11:09 | Oct 10 12:22:21 | ...
        for (int i = 0; i < node->date.size(); i++) {
            // Dado a que las fechas son la suma de tiempo en segundos,
            // se hace lo contrario para conseguir cada uno de sus elementos
            fecha = node->date[i];
            // Operaciones para obtener mes
            mes = fecha / 2678400;
            cout << meses[mes - 1] << " ";
            // Operaciones para obtener dia
            fecha = fecha - mes * 2678400;
            dia = fecha / 86400;
            cout << dia << " ";
            // Operaciones para obtener hora
            fecha = fecha - dia * 86400;
            hora = fecha / 3600;
            cout << hora << ":";
            // Operaciones para obtener minutos
            fecha = fecha - hora * 3600;
            minuto = fecha / 60;
            // Ajustar a formato de impresion. Ej: Feb 10 5:01:22
            if (minuto < 10) {
                cout << "0" << to_string(minuto) << ":";
            } else {
                cout << minuto << ":";
            }
            // Operaciones para obtener los segundos restantes
            fecha = fecha - minuto * 60;
            // Ajustar a formato de impresion. Ej: Apr 29 11:55:09
            if (fecha < 10) {
                cout << "0" << to_string(fecha);
            } else {
                cout << fecha;
            }
            // Separar cada fecha
            cout << " | ";
        }
        // Salto de linea al finalizar impresion
        cout << endl;
    }
    else{
        cout << "No se encontro la IP: " << key << endl;
    }
}

