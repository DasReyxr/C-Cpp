#ifndef CARDACIA_HH
#define CARDIACA_HH
#include<iostream>
using namespace std;

class FrecuenciasCardiacas
{
    //Atributos
    string nombre;
    string apellido;
    int dia, mes, year;
    int edad;
    public:
    FrecuenciasCardiacas(string nombre = "", string apellido ="", int dia = 0, int mes = 1, int year = 0);
    void setNombre(string);
    string getNombre();
    void setApellido(string);
    string getApellido();
    void setDia(int);
    int getDia(void);
    void setMes(int);
    int getMes(void);
    void setyear(int);
    int getyear(void);
    int obtenerEdad();
    void getFrecuenciaCardiacaMaxima();
    void getFrecuenciaCardiacaEsperada();
};

#endif