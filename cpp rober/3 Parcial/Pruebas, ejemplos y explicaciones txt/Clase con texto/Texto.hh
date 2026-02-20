#ifndef TEXTO__HH
#define TEXTO__HH
#include<iostream>
#include<fstream>
using namespace std;

class Texto{
    int cuenta;
    char nombre[40];
    char ciudad[40];
    public:
    fstream archivo;
    Texto(int cuenta = 0, const char* nombre = "", const char* ciudad = "");
    void crearEstructura();
    int capturarCuenta();
    void leer();
    void registrar();
};
#endif