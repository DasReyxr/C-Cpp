/*Ejemplo32
Roberto Lopez Rodriguez 
Manejo de mascaras 
29/05/24"
*/
#include<iostream>
#include<string>

using namespace std;

class Mascaras
{
    //Atributos
    short int mask;
    public:
        Mascaras(short int mask = 0);
        void onMask(short int);
        void offMask(short int);
        //getter
        short int getMask();

};

Mascaras::Mascaras(short int mask)
{
    this->mask = mask;
}
void Mascaras::onMask(short int aux)
{
    this->mask |= aux;
}
void Mascaras::offMask(short int aux)
{
    this->mask &= aux;
}
short int Mascaras::getMask()
{
    return this-> mask;
}
int main()
{
    Mascaras obj, obj1(0xFF);
    cout << hex << obj.getMask() << endl;
    cout << hex << obj1.getMask() << endl;
    obj.onMask(0x11);
    obj1.offMask(0X33);
    cout << hex << obj.getMask() << endl;
    cout << hex << obj1.getMask() << endl;
    cin.get();
    return 0;
}

