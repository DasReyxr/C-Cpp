//Ejemplo 27

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main()
{
    ifstream ifile("test.txt");
    if(!ifile)
    {
        cout << "No encontrado!";
        exit(EXIT_FAILURE);
    }
   string linea;
    while (getline(ifile, linea)) {
        cout << linea << endl;
    }
    ifile.close();
    return 0;
}