#include<iostream>
#include"ejemploastetic.hh"
using namespace std;

/*Una variable y/o constante estatica de una clase es un dato 
comun a todas las instancias que se hagan de esa clase, es decir, 
este tipo de miembros NO FORMAN PARTE de la estancia*/

/*La manera mas correcta de llamar miembros estaticos de una clase 
estando dentro o fuera de ella (main, o, su implementacion) es 
utilizando el nombre de la clase y el opderador de alcance ::
Ejemplo::Ejemplo::numEjemplo = 1 */
Ejemplo::Ejemplo()
{
    Ejemplo::numEjemplo = Ejemplo::numEjemplo +1; //Cada que se crea una istancia se incrementa el contador
    //++Ejemplo::numEjemplo; esto funciona xs
};

int Ejemplo::getnumEjemplo()//<----Ojo aqui Si el miembro
//atributo es static entonves tambien su metodo get
{
    //return this-> numEjemplo //esto es incorrecto
    return Ejemplo::numEjemplo; //Correcto
    //return numEjmeplo; //Correcto
};
/*Hay una restriccion importante que saber, los metodos static
no tienen derecho a utilizar atributos ni metodos de instancia, 
solo tiene derecho al acceso atributos y metodos que tambien sean static*/

void Ejemplo::pruebaA()//Metodo static 
{
    cout << endl << "Soy un metodo estatico!!";
    cout << endl << getnumEjemplo();  //Esto esta OK porque el metodo tambien es static 
    numEjemplo = 0;
    //num = 10; //esto es un error
    //pruebaB(); //Esto es tambien un error, porque no son static!!
}
/*Sin embargo constructores y metodos de instancia (no son static)
pueden usar todo de la clase */
void Ejemplo::pruebaB()
{
    cout << endl << "Yo no soy un metodo static!! " << getnumEjemplo();//static
    numEjemplo = 0;
    num = 10;
}