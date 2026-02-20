#ifndef CAMIGAS_HH
#define CAMIGAS_HH
#include<iostream>
using namespace std;
class Perro
{
    private:
    string nombre;
    int edad;
    public:
    //constructor del perro 
        friend class Gato;
        Perro(string nombre = "", int edad = 0);
};
class Gato 
{
    private:
        string nombre;
        int edad;
        Perro *amigoPerro = nullptr;//Importante poner nullptr
    public:
    //Constructor del gato 
        Gato(string nombre = "", int edad = 0);
    //Destructor de gato(solo si se ocupan punteros en la clase)
        ~Gato(){} //Para poner ~ presiona alt gr y el simolo +
        //Metodo set y get 
        void setAmigoPerro(Perro *);
    //Metodos propios de l~a calse 
    void Amigos();
    //friend void imprimir();
};
#endif