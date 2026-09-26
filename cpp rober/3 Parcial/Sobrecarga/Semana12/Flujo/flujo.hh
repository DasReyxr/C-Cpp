#ifndef FLUO_HH
#define FLUJO_HH

#include<iostream>
using namespace std;
class Coordenadas 
{
    //Atributos 
    int x,y;
    public:
    //Constructor 
        Coordenadas(int x = 0, int y = 0);
        //sobrecarga de cout y cinl
        friend ostream &operator<<(ostream &, const Coordenadas &);
        friend istream &operator>>(istream &, Coordenadas &);
};
#endif