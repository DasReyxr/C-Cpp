/*
------ Orlando Reyes ------
--------- Auf Das ---------
------- GaussJordan -------
-------- 5/03/2026 --------

*/

// ------- Main Library -------
#include "main.h"
#include "GaussJordan.h"
#include "st7735.h"
#include "fonts.h"
#include "display_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --------- Function ---------
// ----------- Main -----------

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



void Resistivo(float R[7]) {
    // Allocate matrix dynamically to match GaussJordanResult expectations
    float **matrix = (float **)malloc(7 * sizeof(float *));
    float *vec = (float *)malloc(7 * sizeof(float));

    for (int i = 0; i < 7; i++) {
        matrix[i] = (float *)malloc(7 * sizeof(float));
    }

    // Initialize matrix values
    matrix[0][0] = R[0]; matrix[0][1] = 0;    matrix[0][2] = R[5]; matrix[0][3] = 0;  matrix[0][4] = 0;  matrix[0][5] = R[4];
    matrix[1][0] = 0;    matrix[1][1] = R[1]; matrix[1][2] = R[5]; matrix[1][3] = R[2]; matrix[1][4] = R[3]; matrix[1][5] = 0;
    matrix[2][0] = 1;    matrix[2][1] = -1;   matrix[2][2] = -1;   matrix[2][3] = 0;  matrix[2][4] = 0;  matrix[2][5] = 0;
    matrix[3][0] = 0;    matrix[3][1] = 1;    matrix[3][2] = 0;    matrix[3][3] = -1; matrix[3][4] = 0;  matrix[3][5] = 0;
    matrix[4][0] = 0;    matrix[4][1] = 0;    matrix[4][2] = 0;    matrix[4][3] = 1;  matrix[4][4] = -1; matrix[4][5] = 0;
    matrix[5][0] = 0;    matrix[5][1] = 0;    matrix[5][2] = 1;    matrix[5][3] = 0;  matrix[5][4] = 1;  matrix[5][5] = -1;

    // Initialize vector
    vec[0] = R[6]; vec[1] = 0; vec[2] = 0; vec[3] = 0; vec[4] = 0; vec[5] = 0;

    GaussJordanResult gj = {6, matrix, vec};
    float* result = GaussJordan(gj);

    // Display solutions on screen
    if (result != NULL) {
        displayGaussJordanSolution(result, 6);
    }

    // Free allocated memory when done
    for (int i = 0; i < 6; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vec);
}

void displayGaussJordanSolution(float* solution, int size) {
    // Get current theme from display_ui
    extern ColorTheme currentTheme;

    ST7735_FillScreenFast(currentTheme.bg);

    // Title
    ST7735_WriteString(5, 5, "Soluciones:", Font_11x18, currentTheme.title, currentTheme.bg);

    char buffer[30];
    int y = 30;

    // Display each current value
    for (int i = 0; i < size && i < 6; i++) {
        sprintf(buffer, "I%d = %.4f A", i + 1, solution[i]);
        ST7735_WriteString(5, y, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        y += 15;
    }

    ST7735_WriteString(5, y+10, "Presione Enter...", Font_7x10, currentTheme.secondary_text, currentTheme.bg);

    // Wait for Enter key
    char ch;
    do {
        ch = readchar();
    } while (ch != '\r' && ch != '\n');
}
float* GaussJordan(GaussJordanResult gj){

    for (int i = 0; i < gj.size; i++) {
        float diag = gj.matrix[i][i];
        if (diag == 0) {
            return NULL;  // Return NULL on singular matrix
        }
        for (int j = 0; j < gj.size; j++) {
            gj.matrix[i][j] /= diag;
        }
        gj.vector[i] /= diag;

        for (int k = 0; k < gj.size; k++) {
            if (k != i) {
                float factor = gj.matrix[k][i];
                for (int j = 0; j < gj.size; j++) {
                    gj.matrix[k][j] -= factor * gj.matrix[i][j];
                }
                gj.vector[k] -= factor * gj.vector[i];
            }

        }

    }
    return gj.vector;

}
