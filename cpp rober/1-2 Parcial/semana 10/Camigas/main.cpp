#include<iostream>
#include"camigas.cpp"
using namespace std;

int main()
{
    Perro perrito1("iddie", 5),perrito2("Reyna", 7);
    Gato gatito1("Garfiel", 12), gatito2("Miaurocio", 22);
    gatito1.setAmigoPerro(&perrito1); //&perrito es la direccion de perrito, debido que *amigoperro es un puntero
    gatito1.Amigos();
    gatito2.Amigos();
    gatito2.setAmigoPerro(&perrito2);
    gatito2.Amigos();
    cin.get();
    return 0;
}
