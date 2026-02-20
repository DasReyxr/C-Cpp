//Ejemplo 30

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
ifstream ifile("componentes.txt", ios::binary);
ofstream ofile("componentes2.txt", ios::binary);
if(!(ifile && ofile))
{
    cout << "No se pudo crear el archivo" << endl;
    exit(EXIT_FAILURE);
    //exit(1);
}
ifile.seekg(0, ios::end); //(0,ifile.end)
long tam = ifile.tellg();
ifile.seekg(0, ios::beg);

char *buffer = new char[tam];
ifile.read(buffer,tam);
ofile.write(buffer,tam);

delete[]buffer;
ifile.close();
ofile.close();



cin.get();
return 0;
}