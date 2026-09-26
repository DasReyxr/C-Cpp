/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo 3
semestre: 2
Proposito: Crear una pequeña bas de datos de 
alumnos de la universidad
Escribe un codigo 
Fecha:  12/02/24 
-------------------------------------------*/

//libreria
#include<iostream>
#include<string.h>
using namespace std;

//structs, unions, clases
//Nuevo tipo de dato que estoy creando 
struct Alumno{
    int matricula = 0; 
    string nombre = "", carrera = "", direccion = "";
    float promedio;
};//Acabamos de generar un nuevo dato tipo de Alumno

int main()
{
    Alumno a1 = {6210, "Roberto", "Electronica", "calle123", 5.6}, a2, a3;
    //Alumno segAelec[40];
    string nom = "", car = "", dir = "";
    int mat;
    float pro;
    cout << endl << "Ingresa la matricula del alumno 2: ";
    cin >> a2.matricula;
    fflush(stdin);
    cout << endl << "Ingresa el nombre del alumno 2: ";
    getline(cin, a2.nombre);
    //gets(a2.nombre);
    cout << endl << "Ingresa la carrera del alumno 2: ";
    getline(cin, a2.carrera);
    cout << endl << "Ingresa el promedio del alumno 2: ";
    cin >> a2.promedio;
    fflush(stdin);
    cout << endl << "Ingresa la direccion del alumno 2: ";
    getline(cin, a2.direccion);
    cout << endl << "Id:" << "\t" << "Nombre" << "\t\t" << "carrera" 
        << "\t\t" << "promedio" << "\t" << "Direccion" << endl;
    cout << endl << a1.matricula << "\t" << a1.nombre 
        << "\t\t" << a1.carrera << "\t" << a1.promedio << "\t\t" << a1.direccion;
    

    cout << endl << "Ingresa la matricula del alumno 3: ";
    cin >> mat;
    a3.matricula = mat;
    fflush(stdin);
    cout << endl << "Ingresa el nombre del alumno 3: ";
    getline(cin, nom);
    //strcpy(a3.nombre, nom);
    a3.nombre = nom;
    cout << endl << "Ingresa la carrera del alumno 3: ";
    getline(cin, car);
    a3.carrera = car;
    //strcpy(a3.carrera, car);
    cout << endl << "Ingresa el promedio del alumno 3: ";
    cin >> pro;
    a3.promedio = pro;
    fflush(stdin);
    cout << endl << "Ingresa la direccion del alumno 3: ";
    getline(cin, dir);
    a3.direccion = dir;
    //strcpy(a3.direccion, dir);
    cout << endl << "Id:" << "\t" << "Nombre" << "\t" << "carrera" 
        << "\t\t" << "promedio" << "\t" << "Direccion" << endl;
    cout << endl << a3.matricula << "\t" << a3.nombre 
        << "\t\t" << a3.carrera << "\t" << a3.promedio << "\t\t" << a3.direccion;

    cin.get();
    return 0;
}