/*Roberto Lopez Rodriguez  
Ejemplo 21
Sobrecarga de funciones
11/04/24
*/

#include<iostream>
using namespace std;

class Tiempo
{
    //Atributos 
    int hora, min;
    //Metodos
    public:
        Tiempo(int = 0, int = 0); //Valores implicitos
        //Sobrecarga del operador de suma 
        Tiempo operator +(Tiempo&); //Funiona con o sin friend, aunque se recomienda 
                                           //ponerlo
        void mostrar();
};

//Implementacion
Tiempo::Tiempo(int h, int m) //Las variable son locales
{
    this->hora = h;
    this->min = m;
}

Tiempo Tiempo::operator+(Tiempo &t)
{
    cout << endl << "Estamos entrando a la sobrecarga de operador(+)";
    Tiempo temp;
    temp.hora = this->hora + t.hora;
    temp.min = this->min + t.min;
    if(temp.min >= 60)
    {
        temp.min-= 60; //temp.min = temp.min-60
        temp.hora++;
    }
    return temp;
}

void Tiempo::mostrar()
{
    cout << endl << this->hora << ":" << this->min;
}

int main ()
{
    Tiempo actual(10, 48), despues(3,16), nuevo;
    Tiempo Actual2 = Tiempo(10, 6);
    actual.mostrar();
    despues.mostrar();
    Actual2.mostrar();
    nuevo = actual + despues;
    nuevo.mostrar();    

    //(nuevo + actual(10, 5)).mostrar(); //Hacerlo al vuelo 
    cin.get();
    return 0;
}