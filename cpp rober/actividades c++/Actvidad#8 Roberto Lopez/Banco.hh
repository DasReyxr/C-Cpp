#ifndef BANCO__HH
#define BANCO__HH
#include <iostream>
#include <fstream>
#include<cstring>
using namespace std;
fstream archivo;
class Cliente {
private:
    int numCuenta;
    string nomCliente;
    float monto;
public:
    Cliente(int numCuenta = 0, string nomCliente = "", float monto = 0.0);
    int getCuenta();
    string getNombre();
    float getMonto();
    void setCuenta(int);
    void setNombre(string);
    void setMonto(float);
};
    void creaEstructura();
    int menu();
    void registrarCliente();
    int leerRegistro();
    void leerCliente();
    void mostrarCliente();
    int capturarCuenta();
    void borrarCuenta();
    void abrirArchivo();
    void cerrarArchivo();
#endif