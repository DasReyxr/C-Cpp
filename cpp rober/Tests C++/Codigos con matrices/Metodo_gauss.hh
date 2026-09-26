#ifndef METODOGAUSS_HH
#define METODOGAUSS_HH
#include<iostream>
#include <stdint.h>
using namespace std;
#define NUM 4
class Gauss
{
    float Matrix[NUM][NUM];
    float sol[NUM];
    float I[NUM][NUM] ={0};
    float det = 1;
    uint8_t n;
    public:
    Gauss(uint8_t n = 0);
    ~Gauss();
    void llenadoMatrix();
    void llenadoVec();
    void setMatrix(float mat[NUM][NUM]);
    void getMatrix();
    void Multescalar(int, int, float);
    void camRenglon(int, int, int);
    void resRenglon(int, int, int, float);
    void rowReduction(int);
    void jordanReduction(int);
    void getdeterminantes();
    void inversa();
    void transpuesta();
};
#endif