/*--------------------------------------
Roberto Lopez Rodriguez 
Nombre : ejemplo una clase de c++
semestre: 2
parcial: 2
Proposito: usar clases en c++
Fecha:  29/02/24 
-------------------------------------------*/

#include<iostream>
#include<string.h>
using namespace std;

//prototipado de funciones

//clases
class Caja
{
    //estos son mis atributos
    private: //Los atributos son privados si los definimos como private, o si no estan definidos
        double largo, ancho, alto;
     //estos son mis metodos publicos--- una funcion es igual que un metodo
    public:
        //constructor
        Caja(double large = 0.0, double ancho = 0.0, double alto = 0.0);//constructor vacio
        //Interfaz
        double volumenCaja(){
        };
};
//Implementacion
Caja::Caja(double large = 0.0, double ancho = 0.0, double alto = 0.0);
double Caja::volumenCaja()
{
    return largo*ancho*alto;
};
int main()
{
    Caja obj;
    cout << obj.volumenCaja();
    cin.get();
    return 0;
}