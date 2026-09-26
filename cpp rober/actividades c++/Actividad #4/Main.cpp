/*Roberto Lopez Rodriguez
    17/04/24
*/

#include "Complejos.cpp"
#include<iostream>
using namespace std;

int main ()
{
    Complejo *c1 = new Complejo(1,1);
    Complejo *c2 = new Complejo(2,2);
    Complejo *c3;
    c3 
    = c1->Sumar(c2);
    c3->toString();
    c3 = c1->Restar(c2);
    c3->toString();
    c3 = c1->Dividir(c2);
    c3->toString();
    c3 = c1->Multiplicar(c2);
    c3->toString();
    c3 = c1->multiEscalar(3.5);
    c3->toString();
    if (c2->equals(c3)) {
    cout << endl << "El numero complejo c2 es igual a c3";
    } else {
    cout << endl << "El numero complejo c2 es diferente que  c3";
    }
    delete c1;
    delete c2;
    delete c3;
    cin.get();
    return 0;
}