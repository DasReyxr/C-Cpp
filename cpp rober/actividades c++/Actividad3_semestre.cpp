/*--------------------------------------
Roberto Lopez Rodriguez
Actividad 3
Proposito: Realice un programa en C++ que construya los siguientes módulos:

Ventas. El módulo registra la venta de diferentes productos a un cliente —farmacia—. Obtiene el total de la venta y actualiza el inventario correspondiente. El fin de datos para la venta de un cliente es 0.
Reabastecimiento. Este módulo permite incorporar productos —cantidades— al inventario. El fin de datos es 0.
Nuevos Productos. El módulo permite incorporar nuevos productos al inventario. Los productos se encuentran ordenados en el arreglo por su clave. El fin de datos es 0.
Inventario. El módulo permite imprimir el inventario completo.
Fecha de modificacion: 10/03/24 */

#include<iostream>
#include<string.h>
using namespace std;
struct Nomprod
{
    string prod = "";
};
   
struct Productos
{
    int Clave;
    Nomprod Nombre;
    float Precio = 0.0;
    int Existencia;
};

short nuevoProd(short, Productos *);
void ventas(int, Productos *);
void resbast(int, Productos *);
void invent(int, Productos *);
const int N = 99;
int main()
{
    unsigned short a = 0;
    string modulo = "";
    Productos *inv;
    inv = new Productos[N];
    cout << "Escoja el modulo que quiera acceder (rescuerde utilizar la sintaxis correcta para cada modulo) ";
    cout << endl << "Modulos: " << endl <<  "Ventas" << "\t" << "Rebastecimiento" 
    << "\t\t" << "Agregar productos" <<"\t" <<  "Inventario"<< endl;
    getline(cin, modulo);
    while (modulo != "Salir")
    {
        if (modulo == "Agregar productos") {
            a = nuevoProd(a, inv);
        }
        else if(modulo == "Ventas"){
            ventas(a, inv);
        }else if (modulo == "Rebastecimiento") {
            resbast(a, inv);
        } else if (modulo == "Inventario") {
            invent(a, inv);
        }  else {
            cout << endl << "!!Modulo no valido!!" << endl;
        }
        cout << endl << "Escoja el modulo que quiera ingresar (Esriba -Salir- paraterminar)";
        getline(cin, modulo);
    }
    delete[] inv; 
    cout << "Programa terminado" << endl;
    cin.get();
    return 0;
}



short nuevoProd(short num, Productos *inv) {
    unsigned short n;
   cout <<  "Dame la cantidad de nuevos productos que quieras agregar: " << endl;
   cin >> n;
   cin.ignore();
   for(int i = 0; i < n; i++)
   {
    cout << "Ingresa el nombre del nuevo producto " << (i+1) << ": ";
    getline(cin, inv[num+i].Nombre.prod);
    cout << endl << "Dame el precio: del nuevo producto " << (i+1) << ": ";
    cin >> inv[num+i].Precio;
    cout << endl << "Dame la exsitencia del nuevo producto " << (i+1) << ": ";
    cin >> inv[num+i].Existencia;
    cout << endl << "Dame la clave del nuevo producto " << (i+1) << ": ";
    cin >> inv[num+i].Clave;
    cin.ignore();
   }
    return num + n;
}
void ventas(int num, Productos *inv)
{
    unsigned short  clav, n;
    cout  << "Dame la clave del producto quieres comprar: " << endl;
    cin >> clav;
    cout << "Dame la cantidad del producto que quieras comprar: "<< endl; 
    cin >> n;
    for (int i = 0; i < num;i++)
    {
        if(inv[i].Clave == clav){
            {
            if(inv[i].Existencia >= n){
            inv[i].Existencia-= n;
            cout << "La compra se realizo exitosa";
            return;
                }
            else {
                cout << "La cantidad supera a la existenica de productos" << endl;
                return;
            }
            }
        }
       
           
    }
     cout << endl << "No se encontro el producto o no hay existentes" << endl;
}
void resbast(int num, Productos *inv) {
    unsigned short clav, n;
    cout << "Dame la clave del producto que quieres restablecer:" << endl;
    cin >> clav;
    cout << "Ingrese la cantidad que quiera restablecer: " << endl;
    cin >> n;
    for (int i = 0; i< num;i++)
    {
        if(inv[i].Clave == clav)
        {
            inv[i].Existencia+= n;
            cout << "Ahora hay " << inv[i].Existencia << " en existencia" << endl;
            return;
        }
            
    }
    cout << endl << "No se encontro el producto o no hay existentes" << endl;
}
void invent(int num, Productos *inv) {
    cout << endl << "Inventario de productos";
    for(int i = 0; i < num; i++)
    {
    cout << endl << "Nombre del producto " << (i+1) << ": "<< inv[i].Nombre.prod;
    cout << endl << "Precio del producto " << (i+1)<< ": "<<inv[i].Precio;
    cout << endl << "clave del producto " << (i+1)<< ": "<<inv[i].Clave;
    cout << endl << "Existencia del producto " << (i+1)<< ": "<<inv[i].Existencia;
    }
}