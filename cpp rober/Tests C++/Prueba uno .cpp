/* Roberto lopez Rodriguez 
Proposito: hacer un codigo prueba 
fecha: 03/03/24
*/

#include<iostream>
#include<string.h>
using namespace std;

//Prototipado
void llenado (unsigned int, int[]);

int main ()
{
    cout << "Dame el numero de datos que quieres ordenar ";
    int n;
    cin >> n;
    int VecNum[n];
    llenado (n, VecNum);
}