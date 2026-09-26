/*----------------------------------
Roberto Lopez Rodriguez 
ejemplo29 
usos de tellp y seekp
---------------------------------*/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*
seekg() se utiliza para cambiar la posición del puntero de lectura en un archivo de entrada (ifstream).
Se utiliza para mover el puntero de lectura a una posición específica en el archivo para leer datos desde esa posición.
Por ejemplo, puedes usar seekg(10) para mover el puntero de lectura a la posición 10 en el archivo de entrada.

ios::end especifica una referencia de desplazamiento desde el final del archivo.
ios::beg se inicia una referencia de desplazamiento desde el principio del archivo

La función tellg() se utiliza para obtener la posición actual del puntero de lectura en un archivo de entrada (ifstream).
*/

int main()
{
    ifstream ifile("test.txt");
    if(!ifile)
    {
        cout << "No se pudocrear el archivo!!....";
        exit(1);
    }
    ifile.seekg(2, ios::end);
    int longi = ifile.tellg();
    cout << "Este archivo tiene: " << longi << "bytes!! " << endl;
    ifile.close();
    cin.get();
    return 0;
}
