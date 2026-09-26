//Aqui el interfaz de mi clase ejemplo sobre static
#ifndef EJEMPLOASTETIC_HH
#define EJEMPLOASTETIC_HH

class Ejemplo
{
    //Atributos
    static int numEjemplo;
    int num;
    public:
    //constructor 
    Ejemplo();
    //Metodo get 
    static int getnumEjemplo();
    //Metodo static +
    static void pruebaA();
    void pruebaB();
};
#endif