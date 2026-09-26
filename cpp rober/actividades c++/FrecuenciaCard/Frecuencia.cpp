#include "Frecuencia.hh"
#include<iostream>
using namespace std;

// Constructor de la clase RegistroCardiaco
RegistroCardiaco::RegistroCardiaco(string nombre, int dia, int mes, int anio)
{
    this->nombreCompleto = nombre;
    this->diaNacimiento = dia;
    this->mesNacimiento = mes;
    this->anioNacimiento = anio;
}

// Métodos de configuración y obtención
void RegistroCardiaco::establecerNombre(string nombre)
{
    this->nombreCompleto = nombre;
}

string RegistroCardiaco::obtenerNombre()
{
    return this->nombreCompleto;
}

void RegistroCardiaco::establecerDiaNacimiento(int dia)
{
    this->diaNacimiento = dia;
}

int RegistroCardiaco::obtenerDiaNacimiento()
{
    return this->diaNacimiento;
}

void RegistroCardiaco::establecerMesNacimiento(int mes)
{
    if(mes <= 12)
        this->mesNacimiento = mes;
    else
        this->mesNacimiento = 1;
}

int RegistroCardiaco::obtenerMesNacimiento()
{
    return this->mesNacimiento;
}

void RegistroCardiaco::establecerAnioNacimiento(int anio)
{
    this->anioNacimiento = anio;
}

int RegistroCardiaco::obtenerAnioNacimiento()
{
    return this->anioNacimiento;
}

// Método para calcular la edad
int RegistroCardiaco::calcularEdad()
{
    int diaActual, mesActual, anioActual;
    cout << endl << "Ingrese el día actual: ";
    cin >> diaActual;
    cout << endl << "Ingrese el mes actual: ";
    cin >> mesActual;
    cout << endl << "Ingrese el año actual: ";
    cin >> anioActual;
    
    if(mesActual >= this->mesNacimiento)
    {
        if (diaActual >= this->diaNacimiento){
            this->edad = anioActual - this->anioNacimiento;
        }
    }
    else 
        this->edad = anioActual - (this->anioNacimiento + 1);
    
    return this->edad;
}

// Métodos para obtener las frecuencias cardíacas
void RegistroCardiaco::obtenerFrecuenciaMaxima()
{
    int frecuenciaMaxima = 220 - this->edad;
    cout << endl << "La frecuencia cardiaca máxima es " << frecuenciaMaxima << " pulsos por minuto.";
}

void RegistroCardiaco::obtenerFrecuenciaEsperada()
{
    int frecuenciaEsperada = static_cast<float>(220 - this->edad) / 2;
    cout << endl << "La frecuencia cardiaca esperada es " << frecuenciaEsperada << " pulsos por minuto.";
}