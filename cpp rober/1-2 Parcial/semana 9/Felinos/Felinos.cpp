#include<iostream>
#include"felinos.hh"
using namespace std;
//Implementacion 
//la clase que engloba 
Felinos::Felinos(string color, int edad, float peso, string tamano, Tigre tigrito)
{
    this->color = color;
    this->edad = edad;
    this->peso = peso;
    this->tamano = tamano;
}
string Felinos::getColor()
{
    return this->color;
}
int Felinos::getEdad()
{
    return this->edad;
}

float Felinos::getPeso()
{
    return this->peso;
}

string Felinos::getTamamo()
{
    return this->tamano;
}
Felinos::Tigre::Tigre(string habitat, string dieta)
{
    this->habitat = habitat;
    this->dieta = dieta;
}
    
void Felinos::Tigre::Cazar()
{
    cout << endl << "Soy un tigre y estoy cazando";
}
Felinos::Gatito::Gatito(string raza , string conducta , string nombre)
{
    this->raza = raza;
    this->conducta = conducta;
    this->nombre = nombre;
}

void Felinos::Gatito::Jugar()
{
    cout << endl << this->nombre << " esta jugando";
}
void Felinos::Gatito::imprimirDatos()
{
    cout << "Nombre: " << this->nombre << endl;
};