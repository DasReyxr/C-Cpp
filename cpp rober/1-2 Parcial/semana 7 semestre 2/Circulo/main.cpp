/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo de constructores y destructores, puntero thisy set 
y get usando separacion de interfaz
semestre: 2
parcial: 2
Proposito: usar clases en c++
Fecha:  29/02/24 
-------------------------------------------*/

#include<iostream>
#include"circulo.cpp"
using namespace std;
int main ()
{
    Circulo obj1, obj2(5), obj3;
    cout << obj1.getRadio();
    cout << endl << "El area del circulo 2 es: " << obj2.calcularArea();
    cout << endl << "La circuferencia del circulo 2 es: " << obj2.calcularCircunferencia();
    obj1.setRadio(10);
    obj3.setRadio(15);
    cout << endl << "El radio del circulo 1 es: " << obj1.getRadio();
    cout << endl << "El radio del circulo 2 es: " << obj3.getRadio();
    
    cout << endl << "El area del circulo 3 es: " << obj3.calcularArea();
    cout << endl << "La circuferencia del circulo 3 es: " << obj3.calcularCircunferencia();
    cin.get();
    return 0;
}