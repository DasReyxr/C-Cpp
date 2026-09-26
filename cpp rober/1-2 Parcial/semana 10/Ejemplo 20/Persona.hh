#ifndef PERSONA_HH
#define PERSONA_HH
#include<iostream>
using namespace std;

class Persona
{
//Atributos
private:
    double ahorro;
protected:
    int edad;
    string nombre;
    public:
    //Constructor de persona
    Persona(string = "", int = 0, double = 0.0);
    //Metodods get y set 
    int getEdad();
    double getAhorro();
    string getNombre();
    void setEdad(int);
    void setAhorro(double);
    void setNombre(string);
    //Metodos propios de la clase
    string metodoPersonaPublic();
private:
    string metodoPersonaPrivate();
protected:
    string metodoPersonaProtected();
};

#endif