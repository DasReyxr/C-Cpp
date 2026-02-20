#include<iostream>
#include"empleado.hh"
using namespace std;

Empleado::Empleado(int id, double sueldo)
{
    this->id = id;
    this->sueldo = sueldo;
}
int Empleado::getId()
{
    return this->id;
}
double Empleado::getSueldo()
{
    return this->sueldo;
}
void Empleado::setId(int id)
{
    this->id = id;
}
void Empleado::setSueldo(double sueldo)
{
    this->sueldo = sueldo;
}
string Empleado::metodoEmpleadoPublic()
{
    return "Hola soy un metodo empleado publica!!\n";
}
string Empleado::metodoEmpleadoPrivate()
{
    return "Hola soy un metodo empleado privada!!\n";
}
string Empleado::metodoEmpleadoProtected()
{
    return "Hola soy un metodo empleado proctetado!!\n";
}