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
struct Data
{
    int *xPtr = nullptr;
};

int main ()
{
    cout << "Dame cuantos numeros quieres resevar en tu estructra dinamica: ";
    int num;
    cin >> num;
    Data nuevo;
    nuevo.xPtr = new int [num];
    for(int i= 0; i < num;i++)
        *(nuevo.xPtr + i) = i;
    for(int i= 0; i < num;i++)
    cout << endl << nuevo.xPtr[i];
    delete [] nuevo.xPtr;
    cin.get();
    return 0;
}