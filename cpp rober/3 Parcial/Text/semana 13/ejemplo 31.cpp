/*Ejemplo31
Roberto Lopez Rodriguez 
*/
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

void creaEstructura();
int menu();
void registrarCliente();
void leerCliente();
void mostrarCliente();
int capturarCuenta();
fstream archivo;
struct cliente
{
    int numCuenta;
    char nomCliente[40];
    float monto;    
};

int main()
{
    int ans, op;
    archivo.open("banco.dat", ios::binary | ios::in | ios::out);
    if(!archivo)
    {
        cerr << "No existe el archivo!" << endl;
        cout << "Deseas crear la estructura?" << endl;
        cout << "(1) Si\t(0) No";
        cin >> ans;
        if (ans == 0)
            return 1;
        else if(ans == 1)
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
    do
    {
        op = menu();
    if(op==1)
        registrarCliente();
    else if(op == 2)
        leerCliente();
    else if(op == 3)
        mostrarCliente();
    else if(op ==4)
    {
        archivo.close();
        creaEstructura();
        archivo.open("banco.dat", ios::binary | ios::in | ios::out);
    }
    else if(op == 5)
        cout << endl << "Fin de programa!!";
    else
        cout << endl << "La opcion no es valida";
    }while(op != 5);
    archivo.close();
    cin.get();
    return 0;
}
   
void creaEstructura()
{
    archivo.open("banco.dat", ios::binary | ios::out);
    cliente blanco = {0, "", 0};
    for (int i = 0; i < 10; i++)    
        archivo.write((char *)&blanco,sizeof(cliente));  
    cout << "Se generó correctamente el archivo" << endl;
    archivo.close();
}
int menu()
{
    int opc;
    cout << endl << "Menu para probar archivos binarios!!";
    cout << endl << "1.\tRegistrarcliente";
    cout << endl << "2.\tLeer un cliente";
    cout << endl << "3.\tMotrar clientes";
    cout << endl << "4,\tResetear el archivo";
    cout << endl << "4.\tSalir";
    cout << endl << " Elige una opcion";
    cin >>opc;
    return opc;
}

void registrarCliente()
{
    cliente registro;
    cout << endl << "Registro de datos....";
    int cuenta = capturarCuenta();
    cout << endl << "Dame el nombre del cliente: ";
    cin.ignore();
    cin.getline(registro.nomCliente, 40);
    cout << endl << "Dame el monto del liente ";
    cin >> registro.monto;
    registro.numCuenta = cuenta;
    archivo.seekp((cuenta - 1)*sizeof(cliente), ios::beg);
    archivo.write((char*)&registro, sizeof(cliente));
    cout << endl << "El archivo fue guardado exitosamente!!" <<endl;
}
int capturarCuenta()
{
    int cuenta;
    do
    {
        cout << endl << "Ingresa un numero de cuenta: ";
        cin >> cuenta;
        if(cuenta < 1 || cuenta > 10)
            cerr <<  "Error, las cuentas validas estan entr 1 y 10!!";
        

    }while(cuenta < 1 || cuenta > 10);
    fflush(stdin);
    return cuenta;
}
void leerCliente()
{
    cliente blanco = {0, "", 0};
    cliente registro;
    registro = blanco;
    cout << endl << "Consulta de cuenta: ";
    int cuenta = capturarCuenta();
    archivo.seekg((cuenta - 1)*sizeof(cliente));
    archivo.read((char*)&registro, sizeof(cliente));
    if (strlen(registro.nomCliente) == 0) {
        cout << endl << "Registro en blanco!!" << endl;
    }
    else
    {
        cout << endl << "Datos del cliente..." << endl;
        cout << "Nombre:\t" << registro.nomCliente << endl 
        << "Monto" << registro.monto;
    }
}

void mostrarCliente()
{
    cliente registro;
    cout << endl << "Leyendo SECUENCIALMENTE el archivo binario!!";
    archivo.clear();
    archivo.seekg(0);
    cout << endl;
    while(archivo.read((char*)&registro, sizeof(cliente)))
    {
        if(registro.numCuenta !=0)
        {
            cout << endl << "Cuenta: \t";
            cout << endl << "Nombre del cliente: \t";
            cout << endl << "Monto: \t";
        }
    }
    archivo.clear();
    archivo.seekg(0);
}