#ifndef JUGADOR_HH
#define JUGADOR_HH
#include <iostream>
using namespace std;
class Jugador
{
    public:
    string nombre;
    int edad;
    float costo;
    Jugador(string nombre = "", int edad = 0, float costo = 0);
    void setNombre(string);
    string getNombre(void);
    void setEdad(int);
    int getEdad(void);
    void getCosto(float);
    float getCosto(void);
    void llenar(void);
};
class Equipo
{   

    string nome;
    string sede;
    int n;
    public:
    Jugador *j;
    Equipo(string nome = "", string sede = "", int n = 0,Jugador *j = nullptr);
    void setNombrequipo(string);
    string getNombrequipo(void);
    void setCiudad(string);
    string getCiudad(void);
    void setIntegrantes(int);
    int getIntegrantes(void);
    void setJugador(Jugador*);
    Jugador* getJugador(void);
    public:
    friend void imprimir(Equipo&);
};
#endif
//Ya no pude 