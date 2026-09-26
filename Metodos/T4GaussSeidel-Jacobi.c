/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos IV ---
-------- 25/02/2026 --------

*/

// ------- Main Library -------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------

typedef struct {
    int max_it;
    float tol;
} LIMITS;
typedef struct { 
    int size;
    float **matrix; 
    float *vector;
} GaussJordanResult;
// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 100

// --------- Function ---------
GaussJordanResult input(int size);
void printMatrix(GaussJordanResult gj);
int checkDiagonalDominance(GaussJordanResult gj);
void rearrangeForDiagonalDominance(GaussJordanResult gj);
void Jacobi(GaussJordanResult gj, LIMITS limits);
void GaussSeidel(GaussJordanResult gj, LIMITS limits);

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

    // Verificar y reorganizar para dominancia diagonal
    printf("\n--- Verificando dominancia diagonal ---\n");
    if (!checkDiagonalDominance(gj)) {
        printf("ADVERTENCIA: La matriz NO es diagonalmente dominante.\n");
        printf("Intentando reorganizar filas...\n");
        rearrangeForDiagonalDominance(gj);
        printf("\nMatriz reorganizada:\n");
        printMatrix(gj);
        
        if (!checkDiagonalDominance(gj)) {
            printf("\n*** ADVERTENCIA CRITICA ***\n");
            printf("No se pudo lograr dominancia diagonal.\n");
            printf("Los metodos iterativos pueden NO CONVERGER.\n");
            printf("Se recomienda usar eliminacion Gaussiana en su lugar.\n");
            printf("\n¿Desea continuar de todas formas? (1=Si, 0=No): ");
            int continuar;
            scanf("%d", &continuar);
            if (!continuar) return 0;
        } else {
            printf("Exito! Matriz reorganizada con dominancia diagonal.\n");
        }
    } else {
        printf("La matriz ES diagonalmente dominante. Convergencia probable.\n");
    }

    printf("\nQue metodo desea usar?\n1) Jacobi\n2) Gauss-Seidel\n3) Salir\nOpcion: ");
    int op;
    if (scanf("%d", &op) != 1 || (op < 1  || op > 3)){
        printf("Opcion no valida\n");
        return 1;
    }
    printf("Ingrese iteraciones personalizadas (0 para Default: 100 MAX): ");
    int tol_op;
    scanf("%d", &tol_op);
    if (tol_op == 0) tol_op = MAX_ITER;

    printf("Ingrese tolerancia personalizadas (0 para Default: 1E-4): ");
    float tol_op2;
    scanf("%f", &tol_op2);
    if (tol_op2 == 0) tol_op2 = PRECISION_VAL;
    LIMITS limits = {tol_op, tol_op2};
    
    
    if (op == 1) 
        Jacobi(gj, limits);
    else if (op == 2)
        GaussSeidel(gj, limits);
    else {
        printf("Conste\n");
        return 0;
    }
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

int checkDiagonalDominance(GaussJordanResult gj) {
    for (int i = 0; i < gj.size; i++) {
        float diagonal = fabsf(gj.matrix[i][i]);
        float sum = 0.0f;
        for (int j = 0; j < gj.size; j++) {
            if (i != j) {
                sum += fabsf(gj.matrix[i][j]);
            }
        }
        if (diagonal <= sum) {
            return 0; // No es diagonalmente dominante
        }
    }
    return 1; // Es diagonalmente dominante
}

void rearrangeForDiagonalDominance(GaussJordanResult gj) {
    // Intentar reorganizar filas para lograr dominancia diagonal
    int *used = (int *)calloc(gj.size, sizeof(int));
    float **new_matrix = (float **)malloc(gj.size * sizeof(float *));
    float *new_vector = (float *)malloc(gj.size * sizeof(float));
    
    for (int i = 0; i < gj.size; i++) {
        new_matrix[i] = (float *)malloc(gj.size * sizeof(float));
    }
    
    // Para cada columna, encontrar la fila con el elemento diagonal más grande
    for (int col = 0; col < gj.size; col++) {
        int best_row = -1;
        float max_ratio = -1.0f;
        
        for (int row = 0; row < gj.size; row++) {
            if (used[row]) continue;
            
            float diagonal = fabsf(gj.matrix[row][col]);
            float sum = 0.0f;
            for (int j = 0; j < gj.size; j++) {
                if (j != col) sum += fabsf(gj.matrix[row][j]);
            }
            
            float ratio = (sum > 0) ? diagonal / sum : diagonal;
            if (ratio > max_ratio) {
                max_ratio = ratio;
                best_row = row;
            }
        }
        
        if (best_row >= 0) {
            used[best_row] = 1;
            for (int j = 0; j < gj.size; j++) {
                new_matrix[col][j] = gj.matrix[best_row][j];
            }
            new_vector[col] = gj.vector[best_row];
        }
    }
    
    // Copiar de vuelta
    for (int i = 0; i < gj.size; i++) {
        for (int j = 0; j < gj.size; j++) {
            gj.matrix[i][j] = new_matrix[i][j];
        }
        gj.vector[i] = new_vector[i];
        free(new_matrix[i]);
    }
    
    free(new_matrix);
    free(new_vector);
    free(used);
}

void Jacobi(GaussJordanResult gj, LIMITS limits){
    float *x = (float *)calloc(gj.size, sizeof(float));      // valores actuales
    float *x_new = (float *)calloc(gj.size, sizeof(float));  // valores nuevos
    int it = 0;
    int converged = 0;

    printf("\n=== Metodo de Jacobi ===\n");
    printf("it.\t|");
    for (int i = 0; i < gj.size; i++) {
        printf(" x%d\t\t|", i + 1);
    }
    printf(" Error Max(%%)\n");
    printf("----------------------------------------------------------\n");

    while (it < limits.max_it) {
        // Calcular nuevos valores usando valores antiguos (Jacobi)
        for (int i = 0; i < gj.size; i++) {
            x_new[i] = gj.vector[i];
            for (int j = 0; j < gj.size; j++) {
                if (i != j) {
                    x_new[i] -= gj.matrix[i][j] * x[j];
                }
            }
            x_new[i] /= gj.matrix[i][i];
        }

        // Calcular error aproximado
        float max_error = 0.0f;
        for (int i = 0; i < gj.size; i++) {
            float error;
            if (fabsf(x_new[i]) > 1e-10) {
                error = fabsf((x_new[i] - x[i]) / x_new[i]) * 100.0f;
            } else {
                error = fabsf(x_new[i] - x[i]) * 100.0f;
            }
            if (error > max_error) max_error = error;
        }

        // Imprimir iteración
        printf("%d\t|", it + 1);
        for (int i = 0; i < gj.size; i++) {
            printf(" %.6f\t|", x_new[i]);
        }
        printf(" %.4f\n", max_error);

        // Verificar convergencia
        converged = 1;
        for (int i = 0; i < gj.size; i++) {
            if (fabsf(x_new[i] - x[i]) >= limits.tol) {
                converged = 0;
                break;
            }
        }

        if (converged && it > 0) {
            printf("\nConvergencia alcanzada en %d iteraciones\n", it + 1);
            printf("\nSoluciones finales:\n");
            for (int i = 0; i < gj.size; i++) {
                printf("x%d = %.6f\n", i + 1, x_new[i]);
            }
            free(x);
            free(x_new);
            return;
        }

        // Actualizar valores
        for (int i = 0; i < gj.size; i++) {
            x[i] = x_new[i];
        }
        it++;
    }
    
    printf("\nNo se alcanzó convergencia después de %d iteraciones\n", limits.max_it);
    printf("\nUltimos valores:\n");
    for (int i = 0; i < gj.size; i++) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }
    free(x);
    free(x_new);
}

void GaussSeidel(GaussJordanResult gj, LIMITS limits){
    float *x = (float *)calloc(gj.size, sizeof(float));      // valores actuales
    float *x_old = (float *)calloc(gj.size, sizeof(float));  // valores anteriores
    int it = 0;
    int converged = 0;

    printf("\n=== Metodo de Gauss-Seidel ===\n");
    printf("it.\t|");
    for (int i = 0; i < gj.size; i++) {
        printf(" x%d\t\t|", i + 1);
    }
    printf(" Error Max(%%)\n");
    printf("----------------------------------------------------------\n");

    while (it < limits.max_it) {
        // Guardar valores antiguos
        for (int i = 0; i < gj.size; i++) {
            x_old[i] = x[i];
        }

        // Calcular nuevos valores usando valores ya actualizados (Gauss-Seidel)
        for (int i = 0; i < gj.size; i++) {
            x[i] = gj.vector[i];
            for (int j = 0; j < gj.size; j++) {
                if (i != j) {
                    x[i] -= gj.matrix[i][j] * x[j];  // usa valores actualizados
                }
            }
            x[i] /= gj.matrix[i][i];
        }

        // Calcular error aproximado
        float max_error = 0.0f;
        for (int i = 0; i < gj.size; i++) {
            float error;
            if (fabsf(x[i]) > 1e-10) {
                error = fabsf((x[i] - x_old[i]) / x[i]) * 100.0f;
            } else {
                error = fabsf(x[i] - x_old[i]) * 100.0f;
            }
            if (error > max_error) max_error = error;
        }

        // Imprimir iteración
        printf("%d\t|", it + 1);
        for (int i = 0; i < gj.size; i++) {
            printf(" %.6f\t|", x[i]);
        }
        printf(" %.4f\n", max_error);

        // Verificar convergencia
        converged = 1;
        for (int i = 0; i < gj.size; i++) {
            if (fabsf(x[i] - x_old[i]) >= limits.tol) {
                converged = 0;
                break;
            }
        }

        if (converged && it > 0) {
            printf("\nConvergencia alcanzada en %d iteraciones\n", it + 1);
            printf("\nSoluciones finales:\n");
            for (int i = 0; i < gj.size; i++) {
                printf("x%d = %.6f\n", i + 1, x[i]);
            }
            free(x);
            free(x_old);
            return;
        }

        it++;
    }
    
    printf("\nNo se alcanzó convergencia después de %d iteraciones\n", limits.max_it);
    printf("\nUltimos valores:\n");
    for (int i = 0; i < gj.size; i++) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }
    free(x);
    free(x_old);
}
