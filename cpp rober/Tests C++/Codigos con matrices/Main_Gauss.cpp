#include<iostream>
#include"Metodo_gauss.cpp"
using namespace std;

int main()
{
    int num;
    cout << endl << "Dame el tamano de la matriz: ";
    cin >> num;
    Gauss obj(num);
    obj.llenadoMatrix();
    obj.llenadoVec();
    obj.inversa();
    obj.getdeterminantes();
    obj.getMatrix();
    //obj.transpuesta();
    cin.get();
    return 0;    
}