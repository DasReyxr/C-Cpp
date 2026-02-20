#include"Banco.hh"
#include<fstream>
#include<iostream>
using namespace std;


Cliente::Cliente(int numCuenta, string nomCliente, float monto)
{
    this->numCuenta = numCuenta;
    this->nomCliente = nomCliente;
    this->monto = monto;
}
int Cliente::getCuenta() {
    return numCuenta;
}

string Cliente::getNombre() {
    return nomCliente;
}

float Cliente::getMonto() {
    return monto;
}
void Cliente::setCuenta (int cuenta)
{
    this->numCuenta = cuenta;
}
void Cliente::setNombre (string Nombre)
{
    this->nomCliente = Nombre;
}

void Cliente::setMonto(float monto) {
    this->monto = monto;
}
void creaEstructura() {
        archivo.open("banco.dat", ios::binary | ios::out);
        Cliente blanco(0, "", 0);
        for (int i = 0; i < 10; i++)
            archivo.write((char *)&blanco, sizeof(Cliente));
        cout << "Se genero correctamente el archivo" << endl;
        archivo.close();
    }

    int menu() {
        int opc;
        cout << endl << "Menu para probar archivos binarios!!";
        cout << endl << "1.\tRegistrar cliente";
        cout << endl << "2.\tLeer un cliente";
        cout << endl << "3.\tMostrar clientes";
        cout << endl << "4.\tBorrar cliente";
        cout << endl << "5.\tResetear el archivo";
        cout << endl << "6.\tSalir";
        cout << endl << "Elige una opcion: ";
        cin >> opc;
        return opc;
    }

    void registrarCliente() {
        Cliente registro;
        int clientes = leerRegistro();
        if(clientes != 0)
            cout << endl << "Quedan disponibles " << clientes << " cuentas!!";
        else
        {
            cout << endl << "Todas las cuentas estan llenas!!!";
            return;
        }
        cout << endl << "Registro de datos....";
        int cuenta = capturarCuenta();
        archivo.seekp((cuenta - 1) * sizeof(Cliente), ios::beg);
        archivo.read((char*)&registro, sizeof(Cliente));
        if(registro.getCuenta() != 0)
        {
            cout << "La cuenta ya existe";
            return;        
        }
        cout << endl << "Dame el nombre del cliente: ";
        cin.ignore();
        string nombre;
        getline(cin, nombre);
        registro.setNombre(nombre);
        cout << endl << "Dame el monto del cliente: ";
        float monto;
        cin >> monto;
        registro.setMonto(monto);
        registro.setCuenta(cuenta);
        Cliente registr(cuenta, nombre, monto);
        archivo.seekp((cuenta - 1) * sizeof(Cliente), ios::beg);
        archivo.write((char*)&registr, sizeof(Cliente));
        cout << endl << "El archivo fue guardado exitosamente!!" << endl;
        cerrarArchivo();
    }

    int leerRegistro()
    {
        Cliente registro;
        int cont = 0;
        archivo.clear();
        archivo.seekg(0);
       for(int i = 0; i < 10; i++)
       {
        archivo.seekg((i) * sizeof(Cliente));
        archivo.read((char*)&registro, sizeof(Cliente));
        if(registro.getCuenta() == 0)
            cont++; 
       }
        archivo.clear();
        archivo.seekg(0);
        return cont;
    }
    int capturarCuenta() {
        int cuenta;
        do {
            cout << endl << "Ingresa un numero de cuenta (1-10): ";
            cin >> cuenta;
            if (cuenta < 1 || cuenta > 10)
                cerr << "Error, las cuentas validas estan entre 1 y 10!!" << endl;
        } while (cuenta < 1 || cuenta > 10);
        return cuenta;
    }

    void leerCliente() {
        Cliente registro(0, "", 0);
        cout << endl << "Consulta de cuenta: ";
        int cuenta = capturarCuenta();
        archivo.seekg((cuenta - 1) * sizeof(Cliente));
        archivo.read((char*)&registro, sizeof(Cliente));
        if (registro.getNombre() == "") {
            cout << endl << "Registro en blanco!!" << endl;
        } else {
            cout << endl << "Datos del cliente..." << endl;
            cout << "Nombre: " << registro.getNombre() << endl;
            cout << "Monto: " << registro.getMonto() << endl;
        }
    }

    void mostrarCliente() {
        Cliente registro;
        cout << endl << "Leyendo SECUENCIALMENTE el archivo binario!!" << endl;
        archivo.clear();
        archivo.seekg(0);
        while (archivo.read((char*)&registro, sizeof(Cliente))) {
            if (registro.getCuenta() != 0) {
                cout << "Cuenta: " << registro.getCuenta() << endl;
                cout << "Nombre del cliente: " << registro.getNombre() << endl;
                cout << "Monto: " << registro.getMonto() << endl;
                cout << "--------------------------" << endl;
            }
        }
        archivo.clear();
        archivo.seekg(0);
    }

    void borrarCuenta()
    {
        Cliente blanco(0, "", 0);
        cout << "Dame el numero de cuenta que quieres borrar [1-10]: ";
        int cuenta = capturarCuenta();
        archivo.seekp((cuenta - 1) * sizeof(Cliente), ios::beg);
        archivo.write((char*)&blanco, sizeof(Cliente));
        cout << "La cuenta se borro con exito !!";
    }
void abrirArchivo() {
    archivo.open("banco.dat", ios::binary | ios::in | ios::out);
}

void cerrarArchivo() {
    archivo.close();
}