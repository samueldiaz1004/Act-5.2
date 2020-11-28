/*/
Act 5.2 - Actividad Integral sobre el uso de codigos hash

Owen Jauregui Borbon - A01638122
Luis Humberto Sanchez Vaca - A01638029
Samuel Alejandro Diaz del Guante Ochoa - A01637592

Fecha de creacion: 23/11/2020
Fecha de edicion: 29/11/2020
/*/

#include "MyHashTable.h"
using namespace std;

int main()
{
    MyHashTable ht("bitacora2.txt");
    bool opcion;

    do{
        string ip;
        cout << "Ingrese la IP a buscar: ";
        cin >> ip;
        ht.print(ip);
        cout << "Seleccione una opcion:" << endl;
        cout << "Hacer otra consulta - 1" << endl;
        cout << "Salir - 0" << endl;
        cin >> opcion;
    }
    while (opcion);

    return 0;
}
