#ifndef AUTOMOVIL_HPP
#define AUTOMOVIL_HPP

//librerias 
#include<iostream>
using namespace std;
    //Interfaz
    class Automovil
    {
    private:
        string color, modelo, marca, trans;
        int year;
        float precio;
    //Metodos
    public:
    //constructor
        Automovil(string marca = "", string modelo = "", int year = 2023, string color = "", double precio = 0.0, string trans = "");
    //Metodos Set y Get
        void setColor(string);
        void setModelo(string);
        void setMarca(string);
        void setTrans(string);
        void setYear(int);
        void setPrecio(double);
        //Una funcion inline le sugiere al compiladot incrustar el codigo fuente des de donde fue
        //llamada haciendo asi mas rapido la compilacion, pero, esto es una sugernecia 
        //si el compilador cree que no es necesario no lo hara 


        inline string setColor();  
        inline  string setModelo();
        inline string setMarca();
        inline string setTrans();
        inline int setYear();
        inline double setPrecio();

        //Metodos propios de la clase
        void imprimirAuto();

    };
    
    
#endif
    