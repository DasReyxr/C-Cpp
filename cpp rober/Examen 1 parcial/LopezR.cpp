/*Roberto Lopez Rodriguez
Examen Parcial 1

*/



#include<iostream>
#include<string.h>
using namespace std;


struct Material
{
    string Tipo = "";
    int Cantidad = 0;
};
struct Prestamo
{
    string Nombre = "";
    int Id = 0;
    Material mat;
};

//Prototipado
void llenado(int, Prestamo*);
void ordenar(int, Prestamo*);
void imprimir(int, Prestamo*);
const int num = 100;
int main()
{
    int n;
    cout << endl << "Dame el numero de prestamos que quieres relizar (el limite es de 100)" << endl;
    cin >> n;

    Prestamo *prest;
    prest = new Prestamo[num];
    llenado(n, prest);
    ordenar(n, prest);
    imprimir(n, prest);
    delete[] prest;
    cin.get();
    return 0;
}

void llenado(int a, Prestamo *num)
{
    
    for(int i = 0; i < a; i++)
    {
        cin.ignore();
        cout << endl<< "Ingrese el nombre del alumno " << (i+1) << ": "<< endl;
        getline(cin, num[i].Nombre);
        cout << "Ingrese el id del alumno " << (i+1) << ": "<< endl;
        cin >> num[i].Id;
        cin.ignore();
        cout << "Ingrese el tipo de material: "<< endl;
        getline(cin,num[i].mat.Tipo);
        cout << "Ingrese la cantidad de material: "<< endl;
        cin >> num[i].mat.Cantidad;
    }
}
void ordenar(int a , Prestamo*num)
{
    int aux[2]; 
    string auxNom = "", auxTip ="";
    for (int j = 0; j < a; j++){
      
    for (int i = 0;i < j;i++){
        if(num[i].mat.Cantidad >= num[i+1].mat.Cantidad){
            auxNom = num[i+1].Nombre;
            aux[0] = num[i+1].Id;
            auxTip = num[i+1].mat.Tipo;
            aux[1] = num[i+1].mat.Cantidad;

            num[i+1].Nombre = num[i].Nombre;
            num[i+1].Id =num[i].Id;
            num[i+1].mat.Tipo = num[i].mat.Tipo;
            num[i+1].mat.Cantidad= num[i].mat.Cantidad;

            num[i].Nombre = auxNom;
            num[i].Id = aux[0];
            num[i].mat.Tipo = auxTip;
            num[i].mat.Cantidad = aux[1]; 
                }
        }
    }
}


void imprimir(int a, Prestamo *num)
{
    cout << endl << "Nombre " <<"\t" << "Id" <<"\t" << "Tipo" << "\t" << "Cantidad";
    for(int i = 0; i < a; i++)
    {
    cout << endl << num[i].Nombre;
    cout << "\t" << num[i].Id;
    cout << "\t" << num[i].mat.Tipo;
    cout << "\t" << num[i].mat.Cantidad;
    }
}