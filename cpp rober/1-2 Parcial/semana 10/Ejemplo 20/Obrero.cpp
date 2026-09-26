#include<iostream>
#include"Obrero.hh"
using namespace std;

Obrero::Obrero(float hrsExtra, double ppHrsExtra)
{
    this->hrsExtra = hrsExtra;
    this->ppHrsExtra = ppHrsExtra;
}
float Obrero::gethrsExtras()
{
    return this->hrsExtra;
}
double Obrero::getppHrsExtra()
{
    return this->ppHrsExtra;
}
void Obrero::sethrsExtras(float hrsExtra)
{
    this->hrsExtra = hrsExtra;
}
void Obrero::setHrsExtra(double ppHrsExtra)
{
    this->ppHrsExtra = ppHrsExtra;
}
void Obrero::pobandoHerencia()
{
    //Atributos de la clase persona 
    this->nombre = "Juan";
    this->edad = 18;
    //this->ahorro = 0;
    //no podemos dar valores directos a a tributos privados
    //Atributos de la clase Empleado
    this->id = 1234;
    this->sueldo =250;

    cout << endl << this->nombre;
    cout << endl << this->getId();
    cout << endl << this->getSueldo();
    cout << endl << this->metodoEmpleadoProtected();
    cout << endl << this->metodoPersonaProtected();
    cout << endl << this->metodoEmpleadoPublic();
    cout << endl << this->metodoPersonaPublic();
    //cout << endl << this->metodoEmpleadoPrivate();
    //no se puede imprimir metodos privados 
}
string Obrero::metodoObreroPublic()
{
    return "Soy un metodo Obrero publico!! \n";
}
string Obrero::metodoObreroPrivate()
{
    return "Soy un metodo Obrero privado!! \n";
}
string Obrero::metodoObreroProtected()
{
    return "Soy un metodo Obrero protegido!! \n";
}