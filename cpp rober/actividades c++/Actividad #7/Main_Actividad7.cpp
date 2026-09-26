#include"TEntero.cpp"
#include<iostream>
using namespace std;

int main()
{
    TEntero a(10), b(9);
    TEntero c = 2;
    TEntero d;

    c = c + a + b;
    cout << c.getNum() << endl; // 21
    
    d = c - a - c;
    cout << d.getNum() << endl; // -10

     d = a + c*b - b*c + b/c;
    cout << d.getNum() << endl; //??
    
    cin.get();
    return 0;
}