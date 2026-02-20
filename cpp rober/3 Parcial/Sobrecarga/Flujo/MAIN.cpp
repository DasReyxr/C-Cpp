#include<iostream>
#include"flujo.cpp"
using namespace std;

int main()
{
    coordenadas obj1, obj2, obj3(5,3);
    cout << "Capturando con dos lineas de cin independientes: ";
    cout << endl << "Dame los datos para el objeto #1: ";
    cin >> obj1;
    cout << endl << "Dame los datos para el objeto #2: ";
    operator >> (cin,obj2);

    //Primera opción
    cout << "Coordenadas del obj1: " << obj1;

    //Segunda opción
    cout << endl << "Coordenadas del obj 2: ";
    operator << (cout, obj2);

    //Capturar datos en cascada
    cout << endl << "Capturando en cascada 2 datos: ";
    cin >> obj1 >> obj2;

    //Imprimir en cascada
    cout << endl << "Imprimiendo en cascada: ";
    cout << obj1 << obj2;

    cin.get();
    return 0;
}

//Una sobrecarga de funciones o de operadores indica que le puedo realizar más tareas para que las desempeñe correctamente