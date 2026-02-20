#ifndef FLUJO_HH
#define FLUJO_HH

#include<iostream>
using namespace std;

class coordenadas
{
    //Atributos
    int x, y;

    //Métodos
    public:
        coordenadas(int x=0, int y =0);

    //Sobrecarga de cin y cout
        friend ostream &operator<<(ostream &, const coordenadas &);
        friend istream &operator>>(istream &, coordenadas &);


};



#endif