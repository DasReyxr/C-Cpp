#include<iostream>
#include"camigas.hh"
using namespace std;

Perro::Perro(string nombre, int edad)
{
    this->nombre = nombre;
    this->edad = edad;
}
Gato::Gato(string nombre, int edad)
{
    this->nombre = nombre;
    this->edad = edad;
}
void Gato::setAmigoPerro(Perro *perrito)
{
    this->amigoPerro = perrito;
}
void Gato::Amigos()
{
    if(this->amigoPerro)   
        cout << this->nombre << " es amigo del perro " << this->amigoPerro->nombre << endl;
    else 
        cout << this->nombre << "no tiene amigos :(" << endl;
}
/*void Gato::imprimir()
{

}*/