#include<iostream>
#include"cadenas.hh"
#include<string>
using namespace std;

//Implementacion 

cadena::cadena(string cad)
{
    this->cad = cad;
}

string cadena::getCad()
{
    return this->cad;
}
cadena cadena::operator+(cadena &aux)
{
    cadena aux2;
    aux2.cad = this->cad + aux.cad;
    return aux2;    
}
cadena cadena::operator+=(cadena &aux)
{
    this->cad = this->cad + aux.cad;
    return *this; //return this->cad;
}
bool cadena::operator!=(cadena &aux)
{
    bool aux2;
    this->cad != aux.cad ? aux2 = true : false;
    //if(this->cad != aux,cad)
    //aux2 = true;
    //else aux2 = false;
    return aux2;
}
// Operador ternario ? es como un if