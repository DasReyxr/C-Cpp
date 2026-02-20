/*Roberto Lopez Rodriguez  
Ejemplo 21
Sobrecarga de funciones
11/04/24
*/

#include<iostream>
using namespace std;

int Suma(int, int);
float Suma(float, float);
//int Suma(int, int, int );

int main()
{
    cout << endl << "Dame dos valores enteros: ";
    int num1, num2;
    cin >> num1 >> num2;

    cout << endl << "Dame dos valores reales: ";
    float num3, num4;
    cin >> num3 >> num4;

    cout << endl << "La suma entera es: " << Suma(num1, num2);
    cout << endl << "La suma real es: " << Suma(num3, num4);

    cin.get();
    return 0;
}

int Suma(int a, int b)
{
    return (a+b);
}

float Suma(float a, float b)
{
    return (a+b);
}