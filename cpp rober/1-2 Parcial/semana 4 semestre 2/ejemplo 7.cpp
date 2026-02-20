/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo 7
semestre: 2
Proposito: Revisar y declarar arreglos y puntos 
Fecha:  21/02/24 
-------------------------------------------*/
/*
Datos para recordar
x++ = x += 1(los dos soman a x uno osea x = x+1)
x += y (a x sele soma y osea x = x+y)
*/
//librerias 
#include<iostream>
#include<string.h>
using namespace std;

int main ()
{
    int x = 3, y = 7 ;
    int z[5] = {2, 4, 6, 8, 10};
    int *xPtr = nullptr; //
    cout << x << " " << y << endl;
    xPtr = &x;  // a xPtr le paso la direccion de x 
    cout << xPtr << endl; 
    y = *xPtr;  // y ahora vale a lo que apunta xPtr (x)
    cout << y << endl;
    *xPtr = 1;  // mdoificamos la direccion osea a x 
    cout << xPtr << endl;
    cout << x << endl;
    cout << y << endl;

    xPtr = &z[2];// cambiamos la direccion del apuntador xPtr -> &z[2]
    cout << xPtr << endl;
    y =*xPtr; // y tomo el valor de donde apunta xPtr (z[2])
    cout << y << endl;
    *xPtr = 15; // cambio el contenido a donde apunta xPtr  (z[2) = 15) 
    cout << z[2] << endl;

    //Aritmetica de punteros
    x= *xPtr + 5; // en x queda el valor de lo que apunta xPtr (z[2])
                  // x = z[2] + 5
    cout << x << endl;

    *xPtr = *xPtr - 5;//z[2] = z[2] -5 
    cout << z[2] << endl;

    ++*xPtr; //z[2] = z[2] + 1
    *xPtr += 1; //z[2] = z[2] + 1
    cout << z[2] << endl;
    cout << *xPtr << endl;

    x = *(xPtr +1);
    cout << x << endl;
    y = *xPtr; //y = z[2] esto es para verificar que el puntero no ha cambiado 
    cout << y << endl;

    xPtr = xPtr + 1; // xPtr++; o xPtr += 1;
    cout << xPtr << endl;
     y = *xPtr; 
    cout << y << endl;

    xPtr = xPtr + 4; // xPtr++; o xPtr += 1;
    cout << xPtr << endl;
     y = *xPtr; 
    cout << y << endl;
    cin.get();
    return 0;
}