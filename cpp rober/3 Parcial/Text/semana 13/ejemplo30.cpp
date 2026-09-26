/*----------------------------------
Roberto Lopez Rodriguez 
ejemplo30
usos de tellp y seekp
---------------------------------*/


#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main()
{
    ifstream ifile("componentes.txt", ios::binary);
    //fstream file("componentes.txt", ios::binary)
    ofstream ofile("componentes2.txt", ios::binary);
    if(!(ifile && ofile))
    {
        cout << "No se pudocrear el archivo!!....";
        exit(1);
    }
    return 0;
}
