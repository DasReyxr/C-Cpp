



#include<iostream>
#include<string.h>
using namespace std;

int main ()
{
    int n, sum= 0;
    cout << "Dame el numero de datos que quieras imprimir y sumar:" << endl;
    cin >> n;
    int Z[n];
    int *arrayPtr;
    arrayPtr = &Z[0];
    for (int i = 0; i < n;i++)
    {
        
        *(arrayPtr) = i;
        cout << endl << Z[i];
        sum += *arrayPtr; // o *arrayPtr
        arrayPtr ++;
    }
    cout << endl << sum;
    /*arrayPtr = new int [n];
    for (int i = 0; i < n;i++)
    {
        arrayPtr += i;
        *(arrayPtr) = i;
        cout << endl << *(arrayPtr);
    }*/
    return 0;
}