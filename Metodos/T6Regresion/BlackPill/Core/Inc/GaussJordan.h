#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H
#include "main.h"

GaussJordanResult input(int size);
void printMatrix(GaussJordanResult gj);
float* GaussJordan(GaussJordanResult gj);
void Resistivo(float* IN);
void displayGaussJordanSolution(float* solution, int size);


float get_a0(float x[], float y[], int n, float a1);
float get_a1(float x[], float y[], int n);
void Lineal(poli p);
void Polinomial(poli p);
#endif // GAUSSJORDAN_H