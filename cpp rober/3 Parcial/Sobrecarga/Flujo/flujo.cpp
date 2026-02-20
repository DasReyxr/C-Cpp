#include<iostream>
#include"flujo.hh"
using namespace std;

coordenadas::coordenadas(int x, int y)
{
    this->x=x;
    this->y=y;
}

ostream &operator<<(ostream &co, const coordenadas &aux)
{
    co << "(" << aux.x << ", " << aux.y << ")";
    return co;
}

istream &operator>>(istream &ci, coordenadas &aux)
{
    cout << endl << "Dame el valor de x: ";
    ci >> aux.x;
    cout << endl << "Ahora el de y: ";
    ci >> aux.y;
    return ci;
}