/*Ejemplo32
Roberto Lopez Rodriguez 
Manejo de mascaras 
29/05/24"
*/
#include<iostream>
#include<string>
#include<bitset> 
#include <string>
using namespace std;

int main(){
    int dinero = 15000;
    for(int j = 0; j <1; j++)
    {
        for(int i = 0; i < 12; i++){
            dinero = dinero *1.012;
            dinero += 15000;
        }
        dinero -= 180000;
        cout << dinero << endl;
    }
}