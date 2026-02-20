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

/*
ios::in: Abre el archivo para lectura.
ios::out: Abre el archivo para escritura. Si el archivo existe, su contenido se trunca.
ios::binary: Abre el archivo en modo binario. Si no se especifica, el archivo se abre en modo texto.
ios::ate: (at end) Mueve el puntero de lectura/escritura al final del archivo al abrirlo. Se puede combinar con ios::in o ios::out.
ios::app: (append) Todos los datos escritos se añadirán al final del archivo. Se puede combinar con ios::out.
ios::trunc: (truncate) Si el archivo existe, su contenido se eliminará al abrirlo. Este es el comportamiento predeterminado de ios::out.
*/

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
    
    /*file << "Hola" <<  endl;
    file << "Alumnos" << endl;
    file << "de electronica" << endl;*/
    file.close(); //Metodo close
    
    cin.get();
    return 0;
}
