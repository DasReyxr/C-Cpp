
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream ifile("ejemplo.txt");
    ofstream ofile("copia.txt");

    if (!ifile) {
        cerr << "No se pudo abrir el archivo de entrada archivo_entrada.txt" << endl;
        return 1;
    }
    if (!ofile) {
        cerr << "No se pudo crear el archivo de salida archivo_salida.txt" << endl;
        return 1;
    }
    ifile.seekg(0, ios::end);
    long tam = ifile.tellg();
    ifile.seekg(0, ios::beg);
    char *buffer = new char[tam];
    ifile.read(buffer, tam);
    ofile.write(buffer, tam);
    delete[] buffer;

    ifile.close();
    ofile.close();
    cout << "Archivo copiado con exito." << endl;

    cin.get();
    return 0;
}