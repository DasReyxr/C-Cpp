/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo de malloc y free
semestre: 2
Proposito: Revisar y declarar arreglos y puntos 
Fecha:  26/02/24 
-------------------------------------------*/

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
using namespace std;
int main()
{
    int *xPtr = nullptr;
    cout << "Dame cuantos elementos tendra tu vector dinamico: ";
    int num;
    cin >> num;

    xPtr = (int *)malloc(num*sizeof(int)); //Reserva espacios del tamaño de num enteros
    
    for(int i = 0; i < num; i++)
    {
        cout << endl << "Dame el elememto "<< i+1 << "de tu arreglo dinamico: ";
        cin >> xPtr[i];
    }
    for(int i = 0; i < num; i++)
    {
        cout << endl <<"Elemento " << i+1 << " de tu arreglo dinamico es " << xPtr[i];
    }
    free(xPtr); //libera lo que hay en xPtr 
    cin.get();
    return 0;
}
