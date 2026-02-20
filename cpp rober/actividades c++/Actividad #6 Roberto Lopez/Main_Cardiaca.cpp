#include<iostream>
#include"Cardiaca.cpp"
using namespace std;

int main()
{
    string nom  = "Roberto", apell = "Gutierrez";
    int dia  = 14, year = 2014, mes = 3;
    cout << endl << "Hola, Dime el nombre del paciente: ";
    cin >> nom;
    cout << endl << " Dime el apellido del paciente: ";
    cin >> apell;
    cout << endl << " Dime el dia de nacimiento del paciente: ";
    cin >> dia;
    cout << endl << " Dime el  mes de nacimiento del paciente: ";
    cin >> mes;
    cout << endl << " Dime el  year de nacimiento del paciente: ";
    cin >> year;
    FrecuenciasCardiacas obj1(nom, apell, dia, mes, year);
    cout << endl << "Nombre: " << obj1.getNombre();
    cout << endl << "Apellido: " << obj1.getApellido();
    cout << endl << "Fecha de nacimiento: " << obj1.getDia() << "/" << obj1.getMes() << "/" << obj1.getyear();
    cout << endl << "Edad: " << obj1.obtenerEdad();
    obj1.getFrecuenciaCardiacaEsperada();
    obj1.getFrecuenciaCardiacaMaxima();
    cin.get();
    return 0;
}