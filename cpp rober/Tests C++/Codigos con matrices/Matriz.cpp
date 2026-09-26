#include<iostream>
#include"Metodo_gauss.cpp"
#include"Matriz.hh"
using namespace std;

Matriz::Matriz(short n){
    this->n = n;
    gauss = Gauss(n);
}
void Matriz::llenadomat() {
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
            cout << "Dame la posicion (" << (i + 1) << ", " << (j + 1) << ") de la matriz: ";
            cin >> this->mat[i][j];
        }
    }
}
void Matriz::llenadomat2()
{
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
            cout << "Dame la posicion (" << (i + 1) << ", " << (j + 1) << ") de la matriz: ";
            cin >> this->mat2[i][j];
        }
    }
}
void Matriz::pasarMatGauss() {
    gauss.setMatrix(mat);
}
void Matriz::sumMatriz()
{
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
        this->rMat[i][j] = this->mat[i][j] + this->mat2[i][j];
        }
    }
}
void Matriz::resMatriz()
{
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
        this->rMat[i][j] = this->mat[i][j] - this->mat2[i][j];
        }
    }
}
void Matriz::escalMatriz(int escal)
{
    for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
        this->mat[i][j] *= escal;
        }
    }
}
void Matriz::mulMatriz()
{
     for(int i = 0; i < this->n; i++) {
        for(int j = 0; j < this->n; j++) {
            for(int k = 0; k < this->n; k++){
                this->rMat[i][j] += mat[i][k]*mat2[k][j];
            }
        }
    }
}   