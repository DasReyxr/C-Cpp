/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo con strutcturas dinamicas 
semestre: 2
Proposito: Revisar y declarar arreglos y puntos 
Fecha:  29/02/24 
-------------------------------------------*/

#include<iostream>
#include<string.h>
using namespace std;

//funciones 
int cuadradoPorValor(int);
int cuadradoPorPuntero(int*);
int cuadradoPorReferencia(int&);
int main ()
{
    int x = 2, y = 3, z = 4;
    cout << "x = " << x ;
    cout <<" x cuadrado por valor:" << cuadradoPorValor(x) << endl; 
    cout << "x = " << x << " antes de la llamada a la funcion cuadradoPorPuntero \n";
    
    cout << "y = " << y << " Valor devuelto por cuadradoValor " << cuadradoPorValor(x) << "x\n";
    cuadradoPorPuntero(&y);
    cout << "y = " << y << "Despues de la llamada a la funcion cudraPuntero\n";
    cout << "z = " << z << " antes de la llamada a la funcion cuadradoPorReferncia: ";
    cuadradoPorReferencia(z);
    cout << "z = " << "despues de la llamada a a la funcion cuadrado por referencia\n";
    return 0;
}

int cuadradoPorValor(int a)
{
    return a *=a;
}

int cuadradoPorPuntero(int *bPtr)
{
    *bPtr *= *bPtr;
}

int cuadradoPorReferencia(int &cRef)
{
    cRef *= cRef;
}