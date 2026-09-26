#include<iostream>
using namespace std;
class Matriz
{
    float mat[2][2];
    public:
    Matriz();
    Matriz(float[2][2]);
    Matriz operator +(Matriz &);
    Matriz operator -(Matriz &);
    Matriz operator *(Matriz &);
    void operator =(Matriz &);
    friend ostream &operator<<(ostream &, const Matriz &);
    friend istream &operator>>(istream &, Matriz &);
    void mostrar();
};
Matriz::Matriz()
{}

Matriz::Matriz(float k[2][2]) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            mat[i][j] = k[i][j];
        }
    }
}

Matriz Matriz::operator +(Matriz & m){
    Matriz resmat;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            resmat.mat[i][j] = this->mat[i][j] + m.mat[i][j];
        }
    }
    return resmat;
}
Matriz Matriz::operator -(Matriz & m){
    Matriz resmat;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            resmat.mat[i][j] = this->mat[i][j] - m.mat[i][j];
        }
    }
    return resmat;
}
Matriz Matriz::operator *(Matriz & m){
    Matriz resmat;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++){
                resmat.mat[i][j] += this->mat[i][k]*m.mat[k][j];
            }
        }
    }
    return resmat;
}

void Matriz::mostrar() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
ostream &operator<<(ostream &co, const Matriz &m)
{
    
    for(int i = 0; i < 2; i++) {
        co << "( ";
        for(int j = 0; j < 2; j++) {
            co << m.mat[i][j] << " ";
        }
        co << ")" << endl;
        }
    return co;
}
istream &operator>>(istream &ci, Matriz &m)
{
     for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << endl<< "Dame el valor ( " << i+1 << ", "<< j+1 <<"): ";
            ci >> m.mat[i][j];
        }
        }
    return ci;
}

int main()
{
    float data1[2][2] = {{1, 2}, {3, 4}};
    float data2[2][2] = {{5, 6}, {7, 8}};
    Matriz m1(data1), m2(data2), res;
    operator>>(cin, m1);
    res = m1 - m2;
    operator << (cout, res);
}