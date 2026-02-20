/*
Roberto Lopez Rodriguez 
usos de tellp y seekp
*/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*
seekp():

seekp() se utiliza para cambiar la posición del puntero de escritura en un archivo de salida (ofstream).
Se utiliza para mover el puntero de escritura a una posición específica en el archivo para escribir datos desde esa posición.
Por ejemplo, puedes usar seekp(10) para mover el puntero de escritura a la posición 10 en el archivo de salida.

La función tellp() se utiliza para obtener la posición actual del puntero de escritura en un archivo de salida (ofstream).
*/


int main() {
    long pos;
    ofstream ofile("test.txt");

    if (!ofile) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    ofile << "6553" << endl;

    // Obtener la posición actual en el archivo
    pos = ofile.tellp();
    cout << "Ahora estamos en: " << pos << endl;

    // Mover la posición en el archivo
    ofile.seekp(pos - 4);

    // Escribir en la posición anteriormente obtenida
    ofile << "Hola crayola  " << endl;
    cin.get();
    // Cerrar el archivo
    ofile.close();

    cout << "Terminamos" << endl;

    return 0;
}
