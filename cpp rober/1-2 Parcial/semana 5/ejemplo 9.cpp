/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo de calloc y free
semestre: 2
Proposito: Revisar y declarar arreglos y puntos 
Fecha:  27/02/24 
-------------------------------------------*/

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
using namespace std;

int main()
{
    int *xPtr = nullptr, sum = 0;
    xPtr = (int *)calloc(10, sizeof(int));
    if ( xPtr == nullptr)
    {
        cerr << "Error1 memoria no reservada"; //mensaje de error del cout 
        return 1;
    }
   cout << "Acumulando los valores de la memoria:" << endl;
   for (int i = 0; i < 10; ++i) //++i es igual a i++
   {
    *(xPtr +i) = i;
    sum += *(xPtr + i);
    cout << "Suma = " << sum << endl; 
   }
    //cout << "Suma = " << sum;
    free(xPtr);
    cin.get();
    return 0;

}