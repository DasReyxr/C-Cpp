#include<iostream>
#include"Fecha.cpp"
using namespace std;

int main()
{
    Fecha obj1, obj2(30, 4, 2024);
    obj1.setDia(24); 
    obj1.setMes(15);
    obj1.setyear(2013);
    obj1.MostrarFecha();//Debido a que esta limitado el mes solo muestra 1 en vez de 15
    obj2.MostrarFecha();//Debido a que esta dentro del rango si muestra el mes7
    cin.get();
    return 0;
}