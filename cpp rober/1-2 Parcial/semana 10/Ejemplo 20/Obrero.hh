#ifndef OBRERO_HH
#define OBRERO_HH
#include<iostream>
#include"empleado.hh"
using namespace std;

class Obrero: public Empleado
{
    //Atributos
    protected:
        float hrsExtra;
        double ppHrsExtra;
    public:
    Obrero(float = 0.0, double = 0.0);
    float gethrsExtras();
    double getppHrsExtra();
    void sethrsExtras(float);
    void setHrsExtra(double);
    //Metodod propios de la clase
    void pobandoHerencia();
    string metodoObreroPublic();
private:
    string metodoObreroPrivate();
protected:
    string metodoObreroProtected();
};
#endif