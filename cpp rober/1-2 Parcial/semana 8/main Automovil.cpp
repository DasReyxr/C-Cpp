#include<iostream>
#include"autmovil.cpp"

int main()
{
    Automovil carro1, carro2("Mazda", "2", 2018, "Rojo", 1260000.5, "Manual");
    carro2.imprimirAuto();

    cin.get();
    return 0;
}