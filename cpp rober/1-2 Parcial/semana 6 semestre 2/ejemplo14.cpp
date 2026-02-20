/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo de constructores y destructores 
semestre: 2
parcial: 2
Proposito: usar clases en c++
Fecha:  29/02/24 
-------------------------------------------*/

#include<iostream>
using namespace std;
#define pi = 3.141592;
//const float pi = 3.141592; //otraforma para crear una constante
class Circulo
{
    //Atributos
    private:
    float radio;

    //Metodos (Interfaz)
    public:
    //construcotres
    Circulo (float radio = 0.0);//Constructor completo
    //Circulo(); //Constructor por defecto
 
    float getRadio(); //Metodo(get para leer)
    void setRadio(float); //Metodo set (para imprimir)
    //Metodos propios de la clase
    float calcularArea();
    float calcularCircunferencia();      
};

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
}

float calcularCircunferencia()
{
}