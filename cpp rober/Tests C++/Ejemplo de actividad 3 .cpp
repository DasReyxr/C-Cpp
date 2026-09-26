/*--------------------------------------
Roberto Lopez Rodriguez
ejemplo de Actividad 3
Proposito: Crear un codigo donde al colocar los colores de las franjas de una resistencia
te porporcione su valor y tolerancia
Fecha de modificacion: 2/03/24 */

#include <iostream>
using namespace std;

struct Producto {
    string Nombre;
    float Precio;
    unsigned short Existencia;
    unsigned short Clave;
};

int nuevoProd(int num, Producto *inv);
void ventas(int num, Producto *inv);
void resbast(int num, Producto *inv);
void invent(int num, Producto *inv);
const int N = 99;
int main() {
    int a = 0;
    Producto *inv = new Producto[N]; // Crear un arreglo dinámico de productos
    string modulo;

    cout << "Escoja el modulo que quiera acceder (recuerde utilizar la sintaxis correcta para cada modulo)" << endl;
    cout << "Modulos:" << endl << "Ventas\tRebastecimiento\tAgregar productos\tInventario" << endl;
    getline(cin, modulo);

    while (modulo != "Salir") {
        if (modulo == "Agregar productos") {
            a = nuevoProd(a, inv);
        } else if (modulo == "Ventas") {
            ventas(a, inv);
        } else if (modulo == "Rebastecimiento") {
            resbast(a, inv);
        } else if (modulo == "Inventario") {
            invent(a, inv);
        } else {
            cout << "¡Módulo no válido!" << endl;
        }
        
        cout << endl << "Escoja el módulo que quiera ingresar (Escriba -Salir- para terminar): ";
        getline(cin, modulo);
    }

    delete[] inv; 
    cout << "Programa terminado" << endl;
    return 0;
}

int nuevoProd(int num, Producto *inv) {
    unsigned short n;
    cout << "Dame la cantidad de nuevos productos que quieras agregar: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "Ingresa el nombre del nuevo producto " << (i + 1) << ": ";
        getline(cin, inv[num + i].Nombre);
        cout << "Dame el precio del nuevo producto " << (i + 1) << ": ";
        cin >> inv[num + i].Precio;
        cout << "Dame la existencia del nuevo producto " << (i + 1) << ": ";
        cin >> inv[num + i].Existencia;
        cout << "Dame la clave del nuevo producto " << (i + 1) << ": ";
        cin >> inv[num + i].Clave;
        cin.ignore();
    }

    return num + n;
}

void ventas(int num, Producto *inv) {
    unsigned short clav, n;
    cout << "Dame la clave del producto que quieres comprar: ";
    cin >> clav;
    cout << "Dame la cantidad del producto que quieras comprar: ";
    cin >> n;

    for (int i = 0; i < num; i++) {
        if (inv[i].Clave == clav) {
            if (inv[i].Existencia >= n) {
                inv[i].Existencia -= n;
                cout << "Compra realizada exitosamente" << endl;
                return;
            } else {
                cout << "La cantidad supera la existencia de productos" << endl;
                return;
            }
        }
    }

    cout << "Producto no encontrado o sin existencias" << endl;
}

void resbast(int num, Producto *inv) {
    unsigned short clav, n;
    cout << "Dame la clave del producto que quieres restablecer: ";
    cin >> clav;
    cout << "Ingrese la cantidad que quieras restablecer: ";
    cin >> n;

    for (int i = 0; i < num; i++) {
        if (inv[i].Clave == clav) {
            inv[i].Existencia += n;
            cout << "Producto restablecido exitosamente" << endl;
            return;
        }
    }

    cout << "Producto no encontrado" << endl;
}

void invent(int num, Producto *inv) {
    cout << "Inventario de productos" << endl;
    for (int i = 0; i < num; i++) {
        cout << "Nombre del producto " << (i + 1) << ": " << inv[i].Nombre << endl;
        cout << "Precio del producto " << (i + 1) << ": " << inv[i].Precio << endl;
        cout << "Clave del producto " << (i + 1) << ": " << inv[i].Clave << endl;
        cout << "Existencia del producto " << (i + 1) << ": " << inv[i].Existencia << endl;
    }
}