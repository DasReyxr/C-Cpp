#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class cliente {
private:
    int numCuenta;
    char nomCliente[40];
    float monto;

public:
    fstream archivo;

    cliente(int numCuenta = 0, const char* nomCliente = "", float monto = 0) {
        this->numCuenta = numCuenta;
     strncpy(this->nomCliente, nomCliente, sizeof(this->nomCliente) - 1);
        this->nomCliente[sizeof(this->nomCliente) - 1] = '\0';
    this->monto = monto;
    }

    void creaEstructura() {
        archivo.open("banco.dat", ios::binary | ios::out);
        cliente blanco = {0, "", 0};
        for (int i = 0; i < 10; i++)
            archivo.write((char *)&blanco, sizeof(cliente));
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
        cliente registro;
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
        archivo.seekp((cuenta - 1) * sizeof(cliente), ios::beg);
        archivo.read((char*)&registro, sizeof(cliente));
        if(registro.numCuenta != 0)
        {
            cout << "La cuenta ya existe";
            return;        
        }
        cout << endl << "Dame el nombre del cliente: ";
        cin.ignore();
        cin.getline(registro.nomCliente, 40);
        cout << endl << "Dame el monto del cliente: ";
        cin >> registro.monto;
        registro.numCuenta = cuenta;
        archivo.seekp((cuenta - 1) * sizeof(cliente), ios::beg);
        archivo.write((char*)&registro, sizeof(cliente));
        cout << endl << "El archivo fue guardado exitosamente!!" << endl;
    }

    int leerRegistro()
    {
        cliente registro;
        int cont = 0;
        archivo.clear();
        archivo.seekg(0);
       for(int i = 0; i < 10; i++)
       {
        archivo.seekg((i) * sizeof(cliente));
        archivo.read((char*)&registro, sizeof(cliente));
        if(registro.numCuenta == 0)
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
        cliente registro = {0, "", 0};
        cout << endl << "Consulta de cuenta: ";
        int cuenta = capturarCuenta();
        archivo.seekg((cuenta - 1) * sizeof(cliente));
        archivo.read((char*)&registro, sizeof(cliente));
        if (strlen(registro.nomCliente) == 0) {
            cout << endl << "Registro en blanco!!" << endl;
        } else {
            cout << endl << "Datos del cliente..." << endl;
            cout << "Nombre: " << registro.nomCliente << endl;
            cout << "Monto: " << registro.monto << endl;
        }
    }

    void mostrarCliente() {
        cliente registro;
        cout << endl << "Leyendo SECUENCIALMENTE el archivo binario!!" << endl;
        archivo.clear();
        archivo.seekg(0);
        while (archivo.read((char*)&registro, sizeof(cliente))) {
            if (registro.numCuenta != 0) {
                cout << "Cuenta: " << registro.numCuenta << endl;
                cout << "Nombre del cliente: " << registro.nomCliente << endl;
                cout << "Monto: " << registro.monto << endl;
                cout << "--------------------------" << endl;
            }
        }
        archivo.clear();
        archivo.seekg(0);
    }

    void borrarCuenta()
    {
        cliente blanco = {0, "", 0};
        cout << "Dame el numero de cuenta que quieres borrar [1-10]: ";
        int cuenta = capturarCuenta();
        archivo.seekp((cuenta - 1) * sizeof(cliente), ios::beg);
        archivo.write((char*)&blanco, sizeof(cliente));
        cout << "La cuenta se borro con exito !!";
    }
};

int main() {
    int ans, op;
    cliente obj;
    obj.archivo.open("banco.dat", ios::binary | ios::in | ios::out);
    if (!obj.archivo) {
        cerr << "No existe el archivo!" << endl;
        cout << "Deseas crear la estructura?" << endl;
        cout <<"(1) Si\t(0) No: ";
        cin >> ans;
        if (ans == 0)
            return 1;
        else if (ans == 1) {
            obj.creaEstructura();
            obj.archivo.open("banco.dat", ios::binary | ios::in | ios::out);
        } else {
            cout << "Operacion invalida" << endl;
            return 1;
        }
    }
    
    do
    {
        op = obj.menu();
        if(op==1)
             obj.registrarCliente();
        else if(op == 2)
             obj.leerCliente();
        else if(op == 3)
             obj.mostrarCliente();
        else if(op == 4)
             obj.borrarCuenta();
        else if(op ==5)
        {
            obj.archivo.close();
            obj.creaEstructura();
            obj.archivo.open("banco.dat", ios::binary | ios::in | ios::out);
        }
        else if(op == 6)
            cout << endl << "Fin de programa!!";
        else
            cout << endl << "La opcion no es valida";
    } while(op != 6);
    obj.archivo.close();
    cin.get();
    return 0;
}