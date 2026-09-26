/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo de declaracion un arreglo de punteros en c++
semestre: 2
Proposito: Revisar y declarar arreglos y puntos 
Fecha:  28/02/24 
-------------------------------------------*/

#include<iostream>
#include<string.h>

using namespace std;

int main ()
{
    cout << "Dame la cantidad de numeros que quieres en tu vector: ";
    int num;
    cin >> num;
    int *arrayPtr;
    arrayPtr = new int[num];
    for (int i = 0; i < num; ++i) //++i es igual a i++
   {
     *(arrayPtr+i) = i;
   }
   for (int i = 0; i < num; ++i) //++i es igual a i++
   {
     cout << arrayPtr[i] << ", ";
   }
   delete [] arrayPtr;
    cin.get();
    return 0;
}