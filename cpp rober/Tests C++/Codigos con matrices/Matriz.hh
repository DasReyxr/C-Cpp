#ifndef MATRIZ_HH
#define MATRIZ_HH
#include"Metodo_gauss.hh"
#include<iostream>
using namespace std;
class Matriz
{
    float mat[NUM][NUM], mat2[NUM][NUM], rMat[NUM][NUM];
    short n;
    public:
    Matriz(short n = 0);
    Gauss gauss;
    void llenadomat();
    void llenadomat2();
    void getMatriz();
    void getres();
    void pasarMatGauss();
    void sumMatriz();
    void resMatriz();
    void escalMatriz(int);
    void mulMatriz();
};

#endif