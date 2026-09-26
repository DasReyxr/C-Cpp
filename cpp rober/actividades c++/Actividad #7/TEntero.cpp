#include"TEntero.hh"
#include<iostream>
using namespace std;

TEntero::TEntero(int num)
{
    this->num = num;
}
TEntero TEntero::operator +(TEntero t)
{
    TEntero res;
    res = this->num + t.num;
    return res;
}
TEntero TEntero::operator -(TEntero t)
{
    TEntero res;
    res = this->num - t.num;
    return res;
}
TEntero TEntero::operator *(TEntero t)
{
    TEntero res;
    res = this->num * t.num;
    return res;
}
TEntero TEntero::operator /(TEntero t)
{
    TEntero res;
    res = this->num/t.num;
    return res;
}
int TEntero::getNum()
{
    return this->num;
}
