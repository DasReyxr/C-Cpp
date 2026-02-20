#include "Frecuencia.cpp"
#include<iostream>
using namespace std;

int main()
{
    // Crear un objeto de la clase RegistroCardiaco
    RegistroCardiaco paciente("Juan Pérez", 15, 5, 1990);
    
    // Obtener y mostrar el nombre del paciente
    cout << "Nombre del paciente: " << paciente.obtenerNombre() << endl;
    
    // Calcular y mostrar la edad del paciente
    int edad = paciente.calcularEdad();
    cout << "Edad del paciente: " << edad << " años" << endl;
    
    // Obtener y mostrar la frecuencia cardíaca máxima del paciente
    paciente.obtenerFrecuenciaMaxima();
    
    // Obtener y mostrar la frecuencia cardíaca esperada del paciente
    paciente.obtenerFrecuenciaEsperada();
    
    return 0;
}