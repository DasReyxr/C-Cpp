#include <iostream>
#include "Banco.cpp"

int main() {
    int ans, op;
    Cliente obj;
    archivo.open("banco.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cerr << "No existe el archivo!" << endl;
        cout << "Deseas crear la estructura?" << endl;
        cout << "(1) Si\t(0) No: ";
        cin >> ans;
        if (ans == 0)
            return 1;
        else if (ans == 1) {
            creaEstructura();
            archivo.open("banco.dat", ios::binary | ios::in | ios::out);
        } else {
            cout << "Operacion invalida" << endl;
            return 1;
        }
    }
    
    do {
        op = menu();
        if(op == 1)
            registrarCliente();
        else if(op == 2)
            leerCliente();
        else if(op == 3)
            mostrarCliente();
        else if(op == 4)
            borrarCuenta();
        else if(op == 5) {
            archivo.close();
            creaEstructura();
           archivo.open("banco.dat", ios::binary | ios::in | ios::out);
        }
        else if(op == 6)
            cout << endl << "Fin de programa!!";
        else
            cout << endl << "La opcion no es valida";
    } while(op != 6);

    archivo.close();
    cin.get();
    return 0;
}