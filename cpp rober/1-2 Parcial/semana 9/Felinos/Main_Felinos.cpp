#include<iostream>
#include"felinos.cpp"

int main()
{
    Felinos obj("Verde", 12, 20, "mediano"), obj1;
    cout << endl <<"Este felino es de color: " << obj.getColor();
    cout << endl << "Tiene: " << obj.getEdad() << " years ";

    Felinos::Gatito obj2("simaes", "agresivo", "lucifer");
    obj2.imprimirDatos();
    obj2.Jugar();
    Felinos::Tigre obj3("sabana", "Vegano");
    cin.get();
    return 0;
}