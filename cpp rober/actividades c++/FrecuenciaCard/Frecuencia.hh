#ifndef FRECUENCIA_HH
#define FRECUENCIA_HH
#include<iostream>
using namespace std;

class RegistroCardiaco
{
    // Atributos
    string nombreCompleto;
    int diaNacimiento, mesNacimiento, anioNacimiento;
    int edad;
    
    public:
    // Constructor
    RegistroCardiaco(string nombre = "", int dia = 0, int mes = 1, int anio = 0);
    
    // Métodos de configuración y obtención
    void establecerNombre(string);
    string obtenerNombre();
    void establecerDiaNacimiento(int);
    int obtenerDiaNacimiento();
    void establecerMesNacimiento(int);
    int obtenerMesNacimiento();
    void establecerAnioNacimiento(int);
    int obtenerAnioNacimiento();
    
    // Método para calcular la edad
    int calcularEdad();
    
    // Métodos para obtener las frecuencias cardíacas
    void obtenerFrecuenciaMaxima();
    void obtenerFrecuenciaEsperada();
};

#endif