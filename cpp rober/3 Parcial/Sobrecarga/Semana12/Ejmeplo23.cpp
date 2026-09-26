/*--------------------------------------------
Ejemplo 23
Propostio: Sobregarga de operaciones +, !=, +=
sumar y comparar de una clase

Roberto Lopez Rodriguez 
29/04/24
----------------------------------------------*/


#include<iostream>
#include"cadenas.cpp"
using namespace std;

int main ()
{
    cadena cad1("ie ");
    cadena cad2("uaa ");
    cadena cad3("ags ");
    cadena suma;
    suma = cad1 + cad2; //cad1.operator+(cad2)
    cout<<suma.getCad(); //debe verse isc uaa
    cadena cad4("uaa");
    if (cad4 != cad2)
        cout << "\ncadenas iguales"<< endl;
    else
        cout<<"\ncadenas diferentes"<< endl;
    cadena c1("Hola ");
    cadena c2("alumnos ");
    c1+=c2; // c1.operator+=(c2)
    cout<<c1.getCad(); //debe verse Hola alumnos
    cadena cad5;
    cad5 = cad1 + cad2 + cad3; // cad1.operator+( cad2.operator+(cad3) )
    cout<<cad5.getCad(); //debe verse isc uaa ags
    cin.get();
    return 0;
}