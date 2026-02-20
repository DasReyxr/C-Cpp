#ifndef CLIENTE_HH
#define CLIENTE_HH

#include <iostream>
#include <cstring>

class cliente
{
    int cuenta;
    char nom[40];
    float monto;

public:
    cliente(int cuenta,char* nombre, float monto); 
    int getNumCuenta();  
    char* getNomCliente();  
    float getMonto();  
    void imprimir();  
    void setCliente(int cuenta,char* nombre, float monto);
};

#endif
