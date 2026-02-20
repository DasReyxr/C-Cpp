#ifndef BANCO_HH
#define BANCO_HH

#include <iostream>
#include <fstream>
#include "cliente.hh"

class banco
{
private:
    std::fstream archivo;
    int capturarCuenta();
    void creaEstructura();

public:
    banco();
    ~banco();
    int menu();
    void registrarCliente();
    void leerCliente();
    void mostrarCliente();
    void borrarCliente();
};

#endif
