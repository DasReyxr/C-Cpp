#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H
#include "main.h"

GaussJordanResult input(int size);
void printMatrix(GaussJordanResult gj);
float* GaussJordan(GaussJordanResult gj);
void Resistivo(float* IN);
void displayGaussJordanSolution(float* solution, int size);

#endif // GAUSSJORDAN_H
