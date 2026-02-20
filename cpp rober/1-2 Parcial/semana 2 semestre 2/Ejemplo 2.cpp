/*Roberto Lopez Rodriguez
semestre: 2
ejemplos de usop de cout  u cin
*/

//librerias 
#include<iostream>

//Prototipo de nuestra funcion 
int pow(int, int);

int main()
{
    std:: cout<<"Dame un numero entero positivo: ";
    int num, pot, res;
    std:: cin >> num;
    std:: cout <<"\nDame la potencia: ";
    std:: cin >> pot;
    res = pow(pot, num);
    std::cout<<"El resultado es: " << res;
    return 0;
}    

int pow(int a, int b)
{
    int res = 1;
    for(int i = 0; i < a; i++)
    {
        res = res*b;
    }
    return res;
}