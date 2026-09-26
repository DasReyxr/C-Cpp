#ifndef CIRCULO_HH
#define CIRCULO_HH
//INTERFAZ
class Circulo
{
    //Atributos
    private:
    float radio;

    //Metodos (Interfaz)
    public:
    //construcotres
    Circulo (float radio = 0.0);//Constructor completo
    //Circulo(); //Constructor por defecto
 
    float getRadio(); //Metodo(get para leer)
    void setRadio(float); //Metodo set (para imprimir)
    //Metodos propios de la clase
    float calcularArea();
    float calcularCircunferencia();      
};

#endif