#include<iostream>
#include<stdint.h>
#include"Metodo_gauss.hh"
using namespace std;

Gauss::Gauss(uint8_t n)
{
    this->n = n;
}
Gauss::~Gauss() 
{
}
void Gauss::llenadoMatrix() {
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
            cout << "Dame la posicion (" << (i + 1) << ", " << (j + 1) << ") de la matriz: ";
            cin >> this->Matrix[i][j];
        }
    }
}
void Gauss::llenadoVec() {
    cout << endl <<  "Dame las igualdades de las ecuaciones: ";
for(int i = 0; i < this->n; i++) {
        cout << endl << "Igualdad" << i+1 << ": ";
        cin >> this->sol[i];
    } 
}
void Gauss::setMatrix(float mat[NUM][NUM]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Matrix[i][j] = mat[i][j];
        }
    }
}
void Gauss::getMatrix() {
    for(int i = 0; i < this->n; i++) {
        cout << "( ";
        for(int j = 0; j < this->n; j++)
            cout << this->Matrix[i][j] << " ";
        cout << "| " << this->sol[i];
        cout << " )" << endl;
    }
}

void Gauss::Multescalar(int num, int r, float escal) {
     for(int i = 0; i < this->n; i++) {
        this->Matrix[r][i] *= escal;
    }
    this->det *= 1/escal;
    switch (num){
    case 1:
        this->sol[r] *= escal;
         break;
    case 2:
        for(int i = 0; i < this->n; i++) {
        this->I[r][i] *= escal;
    } 
    break;  
    default:
        break;
    }
}

void Gauss::resRenglon(int num,int r, int r2, float escal) {
    for(int i = 0; i < this->n; i++) {
        this->Matrix[r2][i] -= this->Matrix[r][i] * escal;
    }
    switch (num)
    {
    case 1:
        this->sol[r2] -= this->sol[r]*escal;
         break;
    case 2:
        for(int i = 0; i < this->n; i++) {
        this->I[r2][i] -= this->I[r][i] * escal;
    }
    break;
    default:
        break;
    }
}

void Gauss::camRenglon(int num,int r, int r2) {
    float aux;
    for(int i = 0; i < this->n; i++) {
        aux = this->Matrix[r][i];
        this->Matrix[r][i] = this->Matrix[r2][i];
        this->Matrix[r2][i] = aux;
    }
    this->det *=(-1);
    aux = 0;
     switch (num)
    {
    case 1:
        aux = this->sol[r];
    this->sol[r] = this->sol[r2];
    this->sol[r2] = aux;
         break;
    case 2:
         for(int i = 0; i < this->n; i++) {
        aux = this->I[r][i];
        this->I[r][i] = this->I[r2][i];
        this->I[r2][i] = aux;
        }
    break;
    default:
        break;
    }
    
    
    
}

void Gauss::rowReduction(int num) {
    for(int i = 0; i < this->n; i++) {
        if(this->Matrix[i][i] == 0) {
            for(int k = i + 1; k < this->n; k++) {
                if(this->Matrix[k][i] != 0) {
                    camRenglon(num, i, k);
                    break;
                }
            }
        }

        Multescalar(num, i, 1 / this->Matrix[i][i]);
        for(int j = i + 1; j < this->n; j++) {
            resRenglon(num, i, j, this->Matrix[j][i]);
        }
    }
}

void Gauss::jordanReduction(int num) {
    rowReduction(num);
    for(int i = this->n - 1; i >= 0; i--) {
        for(int j = i - 1; j >= 0; j--) {
            resRenglon(num, i, j, this->Matrix[j][i]);
        }
    }
}
void Gauss::getdeterminantes()
{
    rowReduction(1);
    for(int i = 0; i < this->n; i++){
    det *= this->Matrix[i][i];
    }
    cout << endl << "La determinates es: " << this->det;  
}
void Gauss::inversa(){
    for(int i = 0; i < this->n; i++){
        this->I[i][i] = 1;
    }
    jordanReduction(2);
    for(int i = 0; i < this->n; i++) {
        cout << "( ";
        for(int j = 0; j < this->n; j++)
            cout << this->I[i][j] << " ";
        cout << " )" << endl;
     }
}
void Gauss::transpuesta()
{
    for(int i = 0; i < this->n; i++) {
        cout << "( ";
        for(int j = 0; j < this->n; j++)
            cout << this->Matrix[i][j] << " ";
        cout << " )" << endl;
    }
}