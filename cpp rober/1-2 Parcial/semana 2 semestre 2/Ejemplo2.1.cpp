/*--------------------------------------
Roberto Lopez Rodriguez 
semestre: 2
Proposito:
Escribe un codigo que te permita convertir 
un numero entero en base decimal a su base binaria
Fecha:  07/02/24 
-------------------------------------------*/

//libreria
#include<iostream>
/*Esta linea me sirve para ya no colocar el 
std en cada funcion de iostream (cin o ccout, etc..)*/
using namespace std;
//Prototipo de nuestra funcion 
void conversion(unsigned long);

int main()
{
    cout << "dame un numero entero para convertirlo en binario: ";
    unsigned long numero;
    cin >> numero;
    conversion(numero);

    cin.get();
    return 0; 
}

//implementacion
void conversion(unsigned long num)
{
    int j = 0;
    unsigned short aux;
    unsigned short bin[64];
    do
    {
        
        aux = num/2;
        bin[j] = num%2; 
        num = aux;
        if(aux != 0)
        j++;
        num = aux;
        
    } while (aux);
    
    for (int i = j; i >= 0; i--)
      cout << bin[i] << " ";  
}