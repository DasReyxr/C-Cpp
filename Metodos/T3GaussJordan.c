/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos III ---
-------- 25/02/2026 --------

*/

// ------- Main Library -------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------
typedef struct { 
    int size;
    float **matrix; 
    float *vector;
} GaussJordanResult;

// --------- Function ---------
GaussJordanResult input(int size);
void printMatrix(GaussJordanResult gj);
void GaussJordan(GaussJordanResult gj);
// ----------- Main -----------

int main()
{
    GaussJordanResult gj;
    printf("Ingrese el tamano de la matriz\n");
    int size;
    if (scanf("%d", &size) != 1 || (size < 1)){
        printf("Opcion no valida\n");
        return 1;
    }
    gj= input(size);

    GaussJordan(gj);
    
    return 0;
}

// --------- Functions ---------

GaussJordanResult input(int size){
    printf("Ingresa datos para la matriz %dx%d\n", size, size);
    // Allocate matrix dynamically
    float **matrix = (float **)malloc(size * sizeof(float *));
    float *vector = (float *)malloc(size * sizeof(float)); // Vector de resultados
    for (int i = 0; i < size; i++) {
        matrix[i] = (float *)malloc(size * sizeof(float));
        vector[i] = 0.0f; // Inicializar vector de resultados
    }
    
    // Read data
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("Dato %d %d: ", i + 1, j + 1);
            scanf("%f", &matrix[i][j]);
        }
    }   

    printf("Ingrese los resultados para cada fila:\n");
    for (int i = 0; i < size; i++) {
        printf("Resultado fila %d: ", i + 1);
        scanf("%f", &vector[i]);
    }
    GaussJordanResult result;
    result.size = size;
    result.matrix = matrix;
    result.vector = vector;
    printMatrix(result);

    return result;
}

void printMatrix(GaussJordanResult gj) {
    for (int i = 0; i < gj.size; i++) {
        printf("|\t");
        for (int j = 0; j < gj.size; j++) {
            printf("%0.2f\t", gj.matrix[i][j]);
            
        }
        printf("| %0.2f\n", gj.vector[i]);
    }
    printf("\n");
}

void GaussJordan(GaussJordanResult gj){
    for (int i = 0; i < gj.size; i++) {
        float diag = gj.matrix[i][i];
        if (diag == 0) {
            printf("Error: División por cero en la fila %d\n", i + 1);
            return;
        }
        for (int j = 0; j < gj.size; j++) {
            gj.matrix[i][j] /= diag;
        }
        gj.vector[i] /= diag;
        printf("R%d-> R%d/ %0.2f:\n", i + 1, i + 1, diag);
        printMatrix(gj);
        
        for (int k = 0; k < gj.size; k++) {
            if (k != i) {
                float factor = gj.matrix[k][i];
                printf("R%d-> R%d - %0.2f * R%d:\n", k + 1, k + 1, factor, i + 1);
                for (int j = 0; j < gj.size; j++) {
                    gj.matrix[k][j] -= factor * gj.matrix[i][j];
                }
                gj.vector[k] -= factor * gj.vector[i];
                printMatrix(gj);

            }

        }
        
    }
    
    printf("\n\n======== Resultados ========\n");
    printMatrix(gj);
}