#include<iostream>
#include"Fecha.hh"
using namespace std;

Fecha::Fecha(int dia, int mes, int year)
{
    this->dia = dia;
    this->mes = mes;
    this->year = year;
}

void Fecha::setDia(int dia)
{
    this->dia = dia;
}
void Fecha::setMes(int mes)
{
    if(mes <= 12)
    this->mes = mes;
    else
    mes = 1;
}
void Fecha::setyear(int year)
{
    this->year = year;
}
int Fecha::getDia(void)
{
    return this->dia;
}
int Fecha::getMes(void)
{
    return this->mes;
}
int Fecha::getyear(void)
{
    return this->year;
}

void Fecha::MostrarFecha()
{
    cout << endl << dia << "/" << mes << "/" << year;
}
