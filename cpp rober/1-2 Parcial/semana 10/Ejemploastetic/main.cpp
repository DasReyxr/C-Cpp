#include<iostream>
#include"ejemploastetic.cpp"

int Ejemplo::numEjemplo = 0; //Esta seria la forma de inicializar un atributo 
                             //de tipo static fuera de la clase 
int main()
{
    Ejemplo f1, f2, f3,f4;
    cout << endl << "Total de+ instancias (objetos creados de la clase) creados:" << Ejemplo::getnumEjemplo();
    /*LOS METODOS STATIC NO REQUIEREN DE UNA INSTANCIA (objeto creado a partir de una clase) PARA PODER
    LLAMRALOS SE UTILIZA EL NOMBRE DE LA CLASE :: NOMBRE DEL METODO STATIC*/
    //STATIC
    Ejemplo::pruebaA();
    //Normal
    f1.pruebaB();
    cin.get();
    return 0;
}