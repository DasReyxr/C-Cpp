#include<iostream>
#include"persona.cpp"
#include"empleado.cpp"
#include"Obrero.cpp"
using namespace std;

int main(void)
{
    Empleado emp1(666,500000);
    cout << endl << emp1.getSueldo();
    cout << endl << emp1.metodoEmpleadoPublic();
    //emp1.metodoEmpleadoProtected();
    //emp1.metodoEmpleadoPrivate();
    /*no puedo acceder a metodos privados o protegidcos*/

    Obrero obr1(10, 50.49);
    cout << endl << obr1.metodoEmpleadoPublic();
    cout << endl << obr1.metodoPersonaPublic();
    //cout << endl << obr1.metodoObreroProtected();

    obr1.pobandoHerencia();
    cin.get();
    return 0;
}