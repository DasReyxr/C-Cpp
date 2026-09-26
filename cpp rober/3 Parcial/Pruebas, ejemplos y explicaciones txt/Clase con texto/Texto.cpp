#include"Texto.hh"
#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;

Texto::Texto(int cuenta, const char* nombre, const char* ciudad)
{
    this->cuenta = cuenta;
    for(int i = 0; i < 40 ;i++)
        this->nombre[i] = nombre[i];
    for(int i = 0; i < 40 ;i++)
     this->ciudad[i] = ciudad[i];
}
void Texto::leer(){
    Texto registro;
    cout << endl << "Leyendo SECUENCIALMENTE el archivo binario!!" << endl;
    archivo.clear();
    archivo.seekg(0);
    while (archivo.read((char*)&registro, sizeof(Texto))) {
        if (registro.cuenta != 0) {
            cout << "Cuenta: " << registro.cuenta << endl;
            cout << "Nombre del cliente: " << registro.nombre << endl;
            cout << "Ciudad: " << registro.ciudad << endl;
            cout << "--------------------------" << endl;
        }
    }
    archivo.clear();
    archivo.seekg(0);
 }

void Texto::registrar()
{
    Texto registro;
    cout << endl << "Registro de datos....";
    int cuenta = capturarCuenta();
    registro.cuenta = cuenta;
    cout << endl << "Dame el nombre: ";
    cin.ignore();
    cin.getline(registro.nombre, 40);
    cout << endl << "Dame la ciudad: ";
    cin.ignore();
    cin.getline(registro.ciudad, 40);
    archivo.seekp((cuenta - 1) * sizeof(Texto), ios::beg);
    archivo.write((char*)&registro, sizeof(Texto));
    cout << endl << "El archivo fue guardado exitosamente!!" << endl;
}
int Texto::capturarCuenta() {
    int cuenta;
    do {
        cout << endl << "Ingresa un numero de cuenta (1-10): ";
        cin >> cuenta;
        if (cuenta < 1 || cuenta > 10)
            cerr << "Error, las cuentas validas estan entre 1 y 10!!" << endl;
    } while (cuenta < 1 || cuenta > 10);
    return cuenta;
}
void Texto::crearEstructura() {
    archivo.open("banco.dat", ios::binary | ios::out);
    Texto blanco(0, "", 0);
    for (int i = 0; i < 10; i++)
        archivo.write((char *)&blanco, sizeof(Texto));
    cout << "Se genero correctamente el archivo" << endl;
    archivo.close();
}