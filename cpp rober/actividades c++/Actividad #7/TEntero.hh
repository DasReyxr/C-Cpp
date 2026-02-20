#ifndef TENTERO_HH
#define TENTERO_HH
#include<iostream>
using namespace std;

class TEntero
{
    int num;
    public:
    TEntero(int num = 0);
    TEntero operator +(TEntero);
    TEntero operator -(TEntero);
    TEntero operator *(TEntero);
    TEntero operator /(TEntero);
    int getNum();
};
#endif