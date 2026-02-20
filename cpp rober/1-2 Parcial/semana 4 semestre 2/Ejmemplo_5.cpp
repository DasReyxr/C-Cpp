/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo 4 completo 
semestre: 2
Proposito: Crear una pequeña bas de datos de 
alumnos de la universidad pero con funciones
Escribe un codigo 
Fecha:  13/02/24 
-------------------------------------------*/
#include<iostream>
#include<string.h>
using namespace std;
//structs

struct Codigo
{
    string franja1 = "", franja2 = "", franja3 = "", franja4 = "";

};
struct Resistor 
{
    float valor = 0.0, watts = 0.0;
    Codigo colores;
};
//protoripado
void lecturaRes(unsigned short, Resistor *);

int main(){
    cout << "Dame cuantas resistencias vas a capturar: ";
    unsigned short num;
    cin >> num;
    Resistor *rest;
    rest = new Resistor[num];
    lecturaRes(num, rest);
    //delete [] rest;
    cin.get();
    return 0;
}
void lecturaRes(unsigned short num, Resistor *resVal){
    for (int i = 0; i < num; i++)
    {
    cout << endl << "Dame el precio del resistor: ";
    cin >> resVal[i].valor;
    cout << endl << "Dame los watts que soporta el resitor: ";
    cin >> resVal[i].watts;
    fflush(stdin);
    cout << endl << "Ingresa el color de la primera franja del resistor: ";
    getline(cin, resVal[i].colores.franja1);
    cout << endl << "Ingresa el color de la segunda franja del resistor: ";
    getline(cin, resVal[i].colores.franja2);
    //fflush(stdin);
    cout << endl << "Ingresa el color de la tercera franja del resistor: ";
    getline(cin, resVal[i].colores.franja3);
    cout << endl << "Ingresa el color de la cuarta franja del resistor: ";
    getline(cin, resVal[i].colores.franja4);
    }
}
