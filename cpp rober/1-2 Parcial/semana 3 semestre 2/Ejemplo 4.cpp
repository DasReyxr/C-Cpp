/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo 4
semestre: 2
Proposito: Crear una pequeña bas de datos de 
alumnos de la universidad pero con funciones
Escribe un codigo 
Fecha:  13/02/24 
-------------------------------------------*/
//librerias
#include<iostream>
#include<string.h>
using namespace std;

//structs, unions, clases
struct Alumno{
    int matricula = 0; 
    string nombre = "", carrera = "", direccion = "";
    float promedio = 0;
};

//prototipado
void llenado(int, Alumno*);
void imprimir(int, Alumno*);

int main()
{
    cout << "Cuantos alumnos quieres capturar: ";
    int num;
    cin >> num;
    Alumno AlumVec[num];
    llenado(num, AlumVec);
    imprimir(num, AlumVec);
     cin.get();
    return 0;
}

void llenado(int n, Alumno *alumVec)
{
   for(int i = 0; i < n; i++)
   {
    cout << endl << "Ingresa la matricula del alumno " << (i+1) << ": ";
    cin >> alumVec[i].matricula;
    fflush(stdin);
    cout << endl << "Ingresa el nombre del alumno: " << (i+1) << ": ";
    getline(cin, alumVec[i].nombre);
    //gets(a2.nombre);
    cout << endl << "Ingresa la carrera del alumno " << (i+1) << ": ";
    getline(cin, alumVec[i].carrera);
    cout << endl << "Ingresa el promedio del alumno " << (i+1) << ": ";
    cin >> alumVec[i].promedio;
    fflush(stdin);
    cout << endl << "Ingresa la direccion del alumno " << (i+1) << ": ";
    getline(cin, alumVec[i].direccion);

   }
}
void imprimir(int n , Alumno* alumVec)
{
    for(int i = 0; i < n; i++)
   {
    cout << endl << "Id:" << "\t" << "Nombre" << "\t\t" << "carrera" 
        << "\t\t" << "promedio" << "\t" << "Direccion" << endl;
    cout << endl << alumVec[i].matricula << "\t" << alumVec[i].nombre 
        << "\t\t" << alumVec[i].carrera << "\t" << alumVec[i].promedio << "\t\t" << alumVec[i].direccion;
   }
}

class Polinomio{
    int orden;
    int cof;
    int exp;
    Polinomio* pol;
    public:
    Polinomio(int orden = 0, Polinomio* pol = nullptr);
    void setcof(int);
    void setexp(int);
    int getcof();
    int getexp();
    Polinomio operator +(Polinomio&);
    Polinomio operator -(Polinomio&);
    Polinomio operator *(Polinomio&);
    Polinomio operator =(Polinomio&);
    Polinomio operator +=(Polinomio&);
    Polinomio operator -=(Polinomio&);
    Polinomio operator *=(Polinomio&);
    friend ostream &operator<<(ostream &, const Polinomio &);
    friend istream &operator>>(istream &, Polinomio &);
};
