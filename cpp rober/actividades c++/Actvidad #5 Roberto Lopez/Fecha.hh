#ifndef FECHA_HH
#define FECHA_HH

#include<iostream>
using namespace std;

class Fecha
{
    //Atributos
    int dia, mes, year;
    public:
    //Constructor 
    Fecha(int dia = 0, int mes = 1, int year = 0);
    void setDia(int);
    int getDia(void);
    void setMes(int);
    int getMes(void);
    void setyear(int);
    int getyear(void);
    void MostrarFecha();
};

#endif