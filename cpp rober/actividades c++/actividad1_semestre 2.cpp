/*--------------------------------------
Roberto Lopez Rodriguez 
semestre: 2
Proposito:
Escribe un codigo que te permita convertir 
un numero fracionario en base decimal a base binaria
Fecha:  12/02/24 
-------------------------------------------*/
//libreria
#include<iostream>

using namespace std;
//prototipo
void conversion(float);

int main ()
{
    cout << "Dame un numero decimal para convertirlo en binario: ";
    float  numero;
    cin >> numero;
    if(numero <= 1)
    {
        cout  << "no es fraccionario ";
        numero --;
    }
    else
    {
        cout << "0.";
        numero = numero*2;
        conversion(numero);
    }
    
    
    cin.get();
    return 0;
}
void conversion(float num)
{
    
    for(int i = 0; i < 32; i++)
    {
        if(num >= 0.999)
    {
        cout  << "1";
        num--;
    }
    else
    {
        cout << "0";
        num = num*2;
    }
    }
}