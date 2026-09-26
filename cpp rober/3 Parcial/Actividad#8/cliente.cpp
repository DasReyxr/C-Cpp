#include "cliente.hh"
#include <iostream>
#include <cstring>

using namespace std;

cliente::cliente(int cuenta,char* nombre, float monto)
{
    this->cuenta = cuenta;
    strncpy(this->nom, nombre, sizeof(this->nom) - 1);
    this->nom[sizeof(this->nom) - 1] = '\0'; 
    this->monto = monto;
}

int cliente::getNumCuenta()
{
    return this->cuenta;
}

char* cliente::getNomCliente()
{
    return this->nom;
}

float cliente::getMonto()
{
    return this->monto;
}

void cliente::imprimir()
{
    cout << "Cuenta: " << cuenta << endl;
    cout << "Nombre: " << nom << endl;
    cout << "Monto: " << monto << endl;
}

void cliente::setCliente(int cuenta,char* nombre, float monto)
{
    this->cuenta = cuenta;
    strncpy(this->nom, nombre, sizeof(this->nom) - 1);
    this->nom[sizeof(this->nom) - 1] = '\0'; 
    this->monto = monto;
}
