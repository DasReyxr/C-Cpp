#include"Cardiaca.hh"
#include<iostream>
using namespace std;

FrecuenciasCardiacas::FrecuenciasCardiacas(string nombre, string apellido, int dia, int mes, int year)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->dia = dia;
    this->mes = mes;
    this->year = year;
}
void FrecuenciasCardiacas::setNombre(string nombre)
{
    this->nombre = nombre;
}
void FrecuenciasCardiacas::setApellido(string apellido)
{
    this->apellido = apellido;
}

void FrecuenciasCardiacas::setDia(int dia)
{
    this->dia = dia;
}
void FrecuenciasCardiacas::setMes(int mes)
{
    if(mes <= 12)
    this->mes = mes;
    else
    mes = 1;
}
void FrecuenciasCardiacas::setyear(int year)
{
    this->year = year;
}
string FrecuenciasCardiacas::getNombre()
{
    return this->nombre;
}
string FrecuenciasCardiacas::getApellido()
{
    return this->apellido;
}
int FrecuenciasCardiacas::getDia(void)
{
    return this->dia;
}
int FrecuenciasCardiacas::getMes(void)
{
    return this->mes;
}
int FrecuenciasCardiacas::getyear(void)
{
    return this->year;
}
int FrecuenciasCardiacas::obtenerEdad()
{
    int diact, mesact, yearact;
    cout << endl << "Dame el dia actual: ";
    cin >> diact;
    cout << endl << "Dame el mes actual: ";
    cin >> mesact;
    cout << endl << "Dame el year actual: ";
    cin >> yearact;
    
    if(mesact >= this->mes)
    {
        if (diact >= this->dia){
        this->edad = yearact - this->year;
        }
    }
    else 
     this->edad = yearact - (this->year+1);
    return this->edad;
}
void FrecuenciasCardiacas::getFrecuenciaCardiacaMaxima()
{
    int cardiacMax = 220 - this->edad;
    cout << endl << "La frecuencia cardiaca maxima es " << cardiacMax << " pulsos por minuto";
}
void FrecuenciasCardiacas::getFrecuenciaCardiacaEsperada()
{
    int cardiacEsp = static_cast<float>(220 - this->edad)/2;
    cout << endl << "La frecuencia cardiaca esperada es " << cardiacEsp << " pulsos por minuto";
}