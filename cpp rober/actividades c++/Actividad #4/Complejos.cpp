#include<iostream>
#include"Complejos.hh"
#include<iostream>
using namespace std;

Complejo::Complejo(double real, double imaginario)
{
    this->real  = real;
    this->imaginario= imaginario;
}
void Complejo::setReal(double)
{
    this->real = real;
}
void Complejo::setImaginario(double)
{
    this->imaginario = imaginario;
}
double Complejo::getReal()
{
    return this->real;
}
double Complejo::getImaginario()
{
    return this->imaginario;
}
Complejo* Complejo::Sumar(Complejo*complej)
{
    double sumReal = this->real + complej->getReal();
    double sumImaginaria = this->imaginario + complej->getImaginario();
    Complejo* suma = new Complejo(sumReal, sumImaginaria);
    return suma;
}
Complejo* Complejo::Restar(Complejo*complej)
{
    double restReal = this->real - complej->getReal();
    double restImag = this->imaginario - complej->getImaginario();
    Complejo* resta = new Complejo(restReal, restImag);
    return resta;
}
Complejo* Complejo::Multiplicar(Complejo*complej)
{
    double multReal = (this->real* complej->getReal()) - (this->imaginario * complej->getImaginario());
    double multImag =  (this->real* complej->getImaginario()) + (this->imaginario * complej->getReal());
    Complejo* mult = new Complejo(multReal, multImag);
    return mult;
}
Complejo* Complejo::Dividir(Complejo*complej)
{

    double divReal = ((this->real* complej->getReal()) + (this->imaginario * complej->getImaginario()))/
    ((complej->getReal()*complej->getReal())+(complej->getImaginario()*complej->getImaginario()));
    double divImag = ((this->imaginario * complej->getReal()) - (this->real* complej->getImaginario()))/
    ((complej->getReal()*complej->getReal())+(complej->getImaginario()*complej->getImaginario()));
    Complejo* div = new Complejo(divReal, divImag);
    return div;
}
Complejo* Complejo::multiEscalar(double num)
{
    double MultReal = this->real * num;
    double MultImag = this->imaginario *num;
    Complejo*Mult = new Complejo(MultReal, MultImag);
    return Mult;
}
void Complejo::toString()
{
    cout << endl << " (" << this-> real << ", " <<  this->imaginario << "i)";
}
bool Complejo::equals(Complejo*complej)
{
    return (this->real==complej->getReal() && this->imaginario==complej->getImaginario()); 
}