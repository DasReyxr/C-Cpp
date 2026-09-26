#include"circulo.hh"
const float pi = 3.141592;


//Implementaciones de  mi clase
Circulo::Circulo (float radio) //:: es el operador de resolucion de alcance
{
    this->radio=radio;
}    
float Circulo::getRadio()
{
    return this -> radio;
}

void Circulo::setRadio(float radio)
{
    this->radio =radio;
}
float Circulo::calcularArea()
{
    return pi*this->radio*this->radio;
}

float Circulo::calcularCircunferencia()
{
    return 2*pi*this->radio;
}
