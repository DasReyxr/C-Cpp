#include<iostream>
#include"flujo.hh"

using namespace std;

Coordenadas::Coordenadas(int x, int y)
{
    this->x = x;
    this->y = y;
}
ostream &operator<<(ostream &co, const Coordenadas &aux)//Se pone el &operator sin Coordenadas::
{
    co << "("<< aux.x <<", "<<aux.y <<")";
    return co;
}
istream &operator>>(istream &ci, Coordenadas &aux) //Se pone el &operator sin Coordenadas::
{
    cout << endl << "dame el valor de x: ";
    ci >> aux.x;
    cout << endl << "dame el valor de y: ";
    ci >>aux.y;
    return ci;
}