/*
Proposito explicar para que sirve los ios en fstream, ofstream ifstream
*/

/*
ios::in: Indica que el archivo se abrirá para lectura. 
Esto significa que solo se pueden realizar operaciones de lectura en el archivo.

ios::out: Indica que el archivo se abrirá para escritura. 
Esto significa que solo se pueden realizar operaciones de escritura en el archivo.

ios::app: Indica que las operaciones de escritura se agregarán al final del archivo. 
Es útil cuando deseas agregar información al final del archivo sin borrar su contenido previo.

ios::trunc: Si el archivo existe, su contenido se truncará (es decir, se borrará) al abrirlo. 
Se utiliza generalmente con ios::out para asegurarse de que el archivo esté vacío antes de escribir en él.

ios::binary: Indica que el archivo se abrirá en modo binario. 
Esto significa que no habrá ninguna interpretación de caracteres 
y los datos se escribirán o leerán exactamente como están en el archivo.

ios::ate: Indica que el puntero de posición en el archivo se colocará al final después de abrirlo. 
Esto significa que puedes escribir datos en cualquier parte del archivo sin sobrescribir su contenido existente.*/

#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ofstream ofile;
    ofile.open("ejemplo.txt");
    if(!ofile)
    {
        cout << "No puedo crear el archivo ..........";
        exit(EXIT_FAILURE);
    }
    cout << "Escriba lo que quiere imprimir en el archivo de texto: ";
    string cad;
    cin >> cad;
    ofile << cad;
    ofile.close();
    cin.get();
    return 0;
}