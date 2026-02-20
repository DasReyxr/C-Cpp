#ifndef FELINOS_HH
#define FELINOS_HH
#include<iostream>
using namespace std;

class Felinos
{
    //atributos
    public:
    //Felinos(string color = "", int edad  = 0, float peso= 0.0, string tamano = "");
    //Metodo con gets
    string getColor();
    int getEdad();
    float getPeso();
    string getTamamo();
    class Tigre
    {
        //Atributos
        string habitat;
        string dieta;
        
        public:
        Tigre(string habitat = "", string dieta = "");
        void Cazar();
    };
    class Gatito
    {
        //atributos
        
        //Metodos
        public: 
        Gatito(string raza = "", string conducta = "", string nombre = "");
        void Jugar();
        void imprimirDatos();
        private:
            string raza;
            string conducta;
            string nombre;
            Tigre tigrito;
    };
    private:
    //atributos
    string color;
    int edad;
    float peso;
    string tamano;
    Tigre tigrito;
    public:
    Felinos(string color = "", int edad  = 0, float peso= 0.0, string tamano = "", Tigre tigrito);
    void Dormir(Tigre tigrito);
};

#endif