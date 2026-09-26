#include<iostream>
#include"flujo.cpp"
using namespace std;

int main()
{
    Coordenadas obj1, obj2, obj3(5, 6);
    cout << endl << "Capturando con dos lineas de cin independientes";
    cout << endl << "Dame los datos para el obj1: ";
    cin >> obj1; //operator >> (cin, obj1)
    cout << endl <<"Dame los datos para el obj2";
    //1er opcion 
    cin >> obj2; //cin >> obj2
    //2da opcion 
    operator >> (cin, obj1);
    //1er opcion
    cout << endl << "Cooredanadas del obj1 (x, y) = "<< obj1 << endl;
    //2da
    operator << (cout, obj2);

    //En cascada
    cout << endl << "Capturando de cascada 2 datos!";
    cin >>obj1 >> obj2;
    //Imprimir en casada
    cout << endl << "Imprimir en cascada 2 datos!";
    cout << obj1 << obj2;
    
    cin.get();
    return 0;
}

/*Entonces una sobrecarga ya sea de funciones o de operadores
me indica que le puedo asignar mas tareas para que las desempeñe
correctamente*/