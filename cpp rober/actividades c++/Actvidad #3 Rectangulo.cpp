/*Roberto Lopez Rodriguez 
  Actividad 3
  Proposito: Crear una clase Rectángulo con los atributos longitud y anchura
  Fecha: 13/04/24
*/

#include<iostream>
using namespace std;

class Rectangulo
{
    private:
    float largo;
    float ancho;
    public:
    Rectangulo(float largo = 1, float ancho = 1);

    float getLargo();
    float getAncho();
    void setLargo(float);
    void setAncho(float);

    float calcularArea();
    float calcularPerimetro(); 
};

Rectangulo::Rectangulo(float largo, float ancho)
{
    this->largo =largo;
    this->ancho = ancho;
}
float Rectangulo::getLargo()
{
     return this ->largo;
}
float Rectangulo::getAncho()
{
     return this ->ancho;
}
void Rectangulo::setLargo(float largo)
{
    if((largo>0.0)&&(20>largo))
    this->largo = largo;
    else 
    cout << endl << "Valor invalido";
}
void Rectangulo::setAncho(float ancho)
{
    if((ancho>0.0)&&(20>ancho))
    this->ancho =ancho;
    else 
    cout << endl << "Valor invalido";
}
float Rectangulo::calcularArea()
{
    return this->largo*this->ancho;
}
float Rectangulo::calcularPerimetro()
{
    return 2*(this->largo + this->ancho);
}

int main ()
{
    Rectangulo obj1, obj2, obj3;
    /*Como en el objeto 1, los atributos, largo  y anchura, no son menores que 20 y son mayores que 0.0 entonces si captura los valores
    */
    obj1.setLargo(10);
    obj1.setAncho(12);
    cout <<endl << "El rectangulo 1 mide "<< obj1.getLargo() << " de largo";
    cout <<endl << "El rectangulo  1 mide " << obj1.getAncho()<< " de ancho";
    cout << endl << "El area del rectanuglo es: " << obj1.calcularArea();
    cout << endl << "El perimtetro del rectanuglo es: " << obj1.calcularPerimetro();

    obj2.setLargo(30);
    obj2.setAncho(20);
    cout <<endl << "El rectangulo 2 mide "<< obj2.getLargo() << " de largo";
    cout <<endl << "El rectangulo  2 mide " << obj2.getAncho()<< " de ancho";
    /*Sin embargo en el objeto 2 no captura los datos debido a que los atributos, largo  y anchura
    , no mayores que 20*/
    obj2.setLargo(-6);
    obj2.setAncho(-3);
    cout <<endl << "El rectangulo 2 mide "<< obj2.getLargo() << " de largo";
    cout <<endl << "El rectangulo  2 mide " << obj2.getAncho()<< " de ancho";
    /*En el objeto 3 tampoco captura los datos debido a que largo y anchura son menores a 0.0*/
    cin.get();
    return 0;
}