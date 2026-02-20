
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Abrir el archivo en modo de escritura para limpiarlo
    ofstream ofile("test2.txt", ios::trunc);

    // Verificar si el archivo se abrió correctamente
    if (!ofile) {
        cerr << "No se pudo abrir el archivo componentes.txt" << endl;
        return 1;
    }

    // Cerrar el archivo inmediatamente para limpiarlo
    ofile.close();

    cout << "Archivo limpiado con éxito." << endl;

    return 0;
}