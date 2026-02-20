#include "banco.hh"
#include <iostream>
#include <fstream>
#include "cliente.hh"

using namespace std;

banco::banco()
{
    archivo.open("banco.dat", ios::binary | ios::in | ios::out);
    if (!archivo)
    {
        cerr << "No existe el archivo!" << endl;
        cout << "Deseas crear la estructura?" << endl;
        cout << "(1) Si\t(0) No: ";
        int ans;
        cin >> ans;
        if (ans == 0)
            exit(EXIT_FAILURE);
        else if (ans == 1)
        {
            creaEstructura();
            archivo.open("banco.dat", ios::binary | ios::in | ios::out);
        }
        else
        {
            cout << "Operacion invalida";
            exit(EXIT_FAILURE);
        }
    }
}

banco::~banco()
{
    archivo.close();
}

void banco::creaEstructura()
{
    archivo.open("banco.dat", ios::binary | ios::out);
    cliente obj(0, "", 0.0);
    for (int i = 0; i < 10; i++)
        archivo.write(reinterpret_cast<const char*>(&obj), sizeof(cliente)); //reinterpret_cast es un operador en C++ que permite convertir un tipo de puntero en otro tipo de puntero. En este caso, estás convirtiendo un puntero a obj (que es de tipo cliente) a un puntero a const char*.
                                                                                //&obj obtiene la dirección de memoria de obj, es decir, el puntero al objeto obj.
    cout << "Se generó correctamente el archivo" << endl;
    archivo.close();
}

int banco::menu()
{
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

void banco::registrarCliente()
{
    cliente registro(0, "", 0.0);
    cout << endl << "Registro de datos....";
    int cuenta = capturarCuenta();
    archivo.seekg((cuenta - 1) * sizeof(cliente), ios::beg);
    archivo.read(reinterpret_cast<char*>(&registro), sizeof(cliente));
    if (registro.getNumCuenta() != 0)
    {
        cout << "La cuenta ya está ocupada." << endl;
        return;
    }

    char nombre[40];
    float monto;
    cout << "Dame el nombre del cliente: ";
    cin.ignore();
    cin.getline(nombre, sizeof(nombre));
    cout << "Dame el monto del cliente: ";
    cin >> monto;

    registro.setCliente(cuenta, nombre, monto);
    archivo.seekp((cuenta - 1) * sizeof(cliente), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&registro), sizeof(cliente));
    cout << "El archivo fue guardado exitosamente!!" << endl;
}

int banco::capturarCuenta()
{
    int cuenta;
    do {
        cout << "Ingresa un numero de cuenta: ";
        cin >> cuenta;
        if (cuenta < 1 || cuenta > 10)
            cerr << "Error, las cuentas validas estan entre 1 y 10!!" << endl;
    } while (cuenta < 1 || cuenta > 10);
    cin.ignore();
    return cuenta;
}

void banco::leerCliente()
{
    cliente registro(0, "", 0.0);
    cout << "Consulta de cuenta: ";
    int cuenta = capturarCuenta();
    archivo.seekg((cuenta - 1) * sizeof(cliente), ios::beg);
    archivo.read(reinterpret_cast<char*>(&registro), sizeof(cliente));
    if (strlen(registro.getNomCliente()) == 0)
    {
        cout << "Registro en blanco!!" << endl;
    }
    else
    {
        cout << "Datos del cliente..." << endl;
        registro.imprimir();
    }
}

void banco::mostrarCliente()
{
    cliente registro(0, "", 0.0);
    cout << "Leyendo SECUENCIALMENTE el archivo binario!!" << endl;
    archivo.clear();
    archivo.seekg(0);
    while (archivo.read(reinterpret_cast<char*>(&registro), sizeof(cliente)))
    {
        if (registro.getNumCuenta() != 0)
        {
            registro.imprimir();
        }
    }
    archivo.clear();
    archivo.seekg(0);
}

void banco::borrarCliente()
{
    cliente blanco(0, "", 0.0);
    cout << "Borrar cuenta: ";
    int cuenta = capturarCuenta();
    archivo.seekp((cuenta - 1) * sizeof(cliente), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&blanco), sizeof(cliente));
    cout << "Cuenta borrada exitosamente!" << endl;
}

