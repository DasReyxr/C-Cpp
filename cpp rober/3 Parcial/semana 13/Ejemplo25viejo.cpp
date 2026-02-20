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
{                                                //Mascaras utiliza app para agregar texto  y trunc para quitar el texto 
    fstream file("test.txt", ios::in | ios::out | ios::app); //Primer contenido de mi file
                                                 //C:\Users\victo o crea el archivo en el directorio
                                                 //se encuentra mi archivo 
                                                 //la segunda parte es especificar comandos para activar entrada,
                                                 //salida, si quiero escribir secuencialmente o al final o incluso
                                                 //borrar el contenido del archivo
    if(!file)//if(!file)
    {
        cout << "No puedo crear el archivo ..........";
        exit(EXIT_FAILURE);
    }
    
    file << "Hola" <<  endl;
    file << "Alumnos" << endl;
    file << "de electronica" << endl;
    file.close(); //Metodo close
    cout << "El archivo se creo exitosamente";
    cin.get();
    return 0;
}
