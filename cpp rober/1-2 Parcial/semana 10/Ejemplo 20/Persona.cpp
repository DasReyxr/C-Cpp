#include<iostream>
#include"Persona.hh"
using namespace std;

Persona::Persona(string, int, double)
{
    this->nombre = nombre;
    this->edad = edad;
    this->ahorro = ahorro;
}
    
int Persona::getEdad()
{
    return this->edad;
}
double Persona::getAhorro()
{
    return this->ahorro;
}
string Persona::getNombre()
{
    return this->nombre;
}
void Persona::setEdad(int edad)
{
    this->edad = edad;
}
void Persona::setAhorro(double ahorro)
{
    this->ahorro = ahorro;
}
void Persona::setNombre(string nombre)
{
    this->nombre = nombre;
}
string Persona::metodoPersonaPublic()
{
    return "Soy un metodo publica!!\n";
}
string Persona::metodoPersonaPrivate()
{
    return "Soy un metodo privada!!\n";
}
string Persona::metodoPersonaProtected()
{
    return "Soy un metodo proctetado!!\n";
}