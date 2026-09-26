/*
Nombre del programa: Ejemplo25 
Proposito: Manejo de archivos
Metodo close:
Revisiones:
Fecha Nombre Revision 
---------------------------
07/05/2024
*/
#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ofstream ofile;
    ofile.open("test1.txt");
    if(!ofile)
    {
        cout << "No puedo crear el archivo ..........";
        exit(EXIT_FAILURE);
    }
    ofile << "Hola alumnos de 2A de electronica";
    ofile.close();
    ofile << "La escritura en el archivo se ejecuto";
    ofile.close();
    cin.get();
    return 0;
}