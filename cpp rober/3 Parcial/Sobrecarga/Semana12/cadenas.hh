#ifndef CADENAS_HH
#define CADENAS_HH

#include<iostream>
using namespace std;
class cadena
{
    //atributos
    string cad;  
    //METODOS 
    public:
        cadena(string cad = "");
        //metodo get 
        string getCad();
        cadena operator+(cadena &);
        cadena operator+=(cadena &);
        bool operator!=(cadena &);
};


#endif