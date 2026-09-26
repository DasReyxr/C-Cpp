


#include<iostream>
#include<string.h>
using namespace std;

int main ()
{
    int x, y, aux;
    int *xPtr = nullptr, *yPtr = nullptr;
    cout  << "Ingrese el valor de x"<< endl;
    cin >> x;
    cout  << endl << "Ingrese el valor de y"<< endl;
    cin >> y;
    
    xPtr = &x;
    yPtr = &y;
    aux = *yPtr;
    y = *xPtr;
    cout << endl << aux<< endl;
    cout << y << endl;
    cin.get();
    return 0;
}