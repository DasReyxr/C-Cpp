#include"jugador.hh"
#include <iostream>
using namespace std;

Jugador::Jugador(string nombre, int edad, float costo)
{
    this->nombre = nombre;
    this->edad = edad;
    this->costo = costo;
}
void Jugador::setEdad(int edad)
{
    this->edad = edad;
}
void Jugador::setNombre(string nombre)
{
    this->nombre = nombre;
}
void Jugador::getCosto(float costo)
{
    this->costo = costo;
}
string Jugador::getNombre(void)
{
    return this->nombre;
}
int Jugador::getEdad(void)
{
    return this->edad;
}
float Jugador::getCosto(void)
{
    return this->costo;
}
void Jugador::llenar()
{
    int edad;
    float cost;
    string n;
    cout << endl << "Dame el nombre: ";
    cin >> n;
    this ->nombre = n;
    cout << endl << "Dame la edad: ";
    cin >> edad;
    this->edad = edad;
    cout << endl << "Dame el costo: ";
    cin >> cost;
    this->costo = costo;
}

Equipo::Equipo(string nome, string sede, int n, Jugador *j)
{
    this->nome = nome;
    this->sede = sede;
    this->n = n;
    this->j = j;
}
void Equipo::setNombrequipo(string nome)
{
    this->nome = nome;  
}
void Equipo::setCiudad(string sede)
{
    this->sede = sede;
}
void Equipo::setIntegrantes(int n)
{
    this->n = n;
}
void Equipo::setJugador(Jugador*j)
{
    this->j = j;
}
string Equipo::getNombrequipo(void)
{
    return this->nome;
}
string Equipo::getCiudad(void)
{
    return this->sede;
}
int Equipo::getIntegrantes(void)
{
    return this->n;
}
Jugador* Equipo::getJugador(void)
{
    return this->j;
}
void impirmir(Equipo& liga)
{
    cout <<endl << "Equipo: " << liga.getNombrequipo();
    cout << endl << "sede: " << liga.getCiudad();
    for(int i = 0;i<3; i++)
    {
    cout << endl << "Jugador: " << i;
    cout << endl << "Nombre: " << liga.j[i].getNombre();
    cout << endl << "Costo: " << liga.j[i].getCosto();
    cout << endl << "Edad: " << liga.j[i].getEdad();
    }
}
//Ya no pude 