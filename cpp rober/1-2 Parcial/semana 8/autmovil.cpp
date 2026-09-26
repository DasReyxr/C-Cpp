#include<iostream>
#include"automovil.hpp"
using namespace std;
//Implementacion
//construtor
Automovil::Automovil(string marca, string modelo, int year, string color, double precio, string trans)
{
    this->marca = marca;
    this->modelo = modelo;
    this->year = year;
    this->color = color;
    this->precio = precio;
    this->trans = trans;
}

void Automovil::setColor(string)
{
   this->color = color; 
}

void Automovil::setModelo(string)
{
    this->modelo = modelo;
}

void Automovil::setMarca(string)
{
    this->marca = marca;
}
    
void Automovil::setTrans(string)
{
    this->trans = trans;
}

void Automovil::setYear(int)
{
    this->year = year;
}
void Automovil::setPrecio(double)
{
    this->precio = precio;
}

inline string Automovil::setColor()
{
    return this->color; 
} 

inline string Automovil::setModelo()
{
    return this->modelo;
}

inline string Automovil::setMarca()
{
    return this->marca;
}

inline string Automovil::setTrans()
{
    return this->trans;
}

inline int Automovil::setYear()
{
    return this->year;
}
       
inline double Automovil::setPrecio()
 {
   return this->precio;
 }

        //Metodos propios de la clase
 void Automovil::imprimirAuto()
 {
    cout << endl << "Marca: " << this->marca;
    cout << endl << "Modelo: " << this->modelo;
    cout << endl << "Year: " << this->year;
    cout << endl << "Color: " << this->color;
    cout << endl << "Precio: " << this->precio;
    cout << endl << "Transmision: " << this->trans;
 }