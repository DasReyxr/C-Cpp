/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos Vi ---
-------- 06/02/2026 --------
*/

// ------- Main Library -------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------
typedef struct { 
    float initialX; 
    float initialY;
    float stepSize;
    int numSteps; 
} argsInput;

typedef struct { 
    float y;
} Result;


// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10
#define HEUN 1
#define PUNTO_MEDIO 2
#define RALSTON 3
// --------- Function ---------
argsInput input(void);
Result RungeKutta(argsInput p, int option);

float f(float x, float y);

// ----------- Main -----------

int main()
{
    argsInput p = input();
    Result res;
    if (p.stepSize <= 0.0f || p.numSteps <= 0) {
        printf("Error: h y N deben ser positivos.\n");
        return 1;
    }
    printf("Que metodo desea usar?\n1) Heun\n2) Punto Medio\n3) Raltson \n4) Salir\nOpcion: ");
    int methodSelected;
    if (scanf("%d", &methodSelected) != 1 || (methodSelected < 1  || methodSelected > 4)){
        printf("methodSelectedcion no valida\n");
        return 1;
    }
    if(methodSelected == 4) return 0;
    else
        res = RungeKutta(p,methodSelected);
    return 0;
}

// --------- Functions ---------


argsInput input(void){
    argsInput p = {0,0, 0, 0};
    int tmp;
    printf("x0= ");
    // Validacion 
    if (scanf("%f", &p.initialX) != 1) return p;
    printf("y0 = ");
    if (scanf("%f", &p.initialY) != 1) return p;
    printf("step size = ");
    if (scanf("%f", &p.stepSize) != 1) return p;
    printf("num steps = ");
    if (scanf("%d", &p.numSteps) != 1) return p;
    if (p.numSteps <= 0) {
        printf("Error: El número de pasos debe ser positivo.\n");
        printf("Sugerencia: num steps = 1\n");
        if (scanf("%d", &tmp) != 1) return p;
        p.numSteps = tmp;
        if (p.numSteps <= 0) {
            printf("Error: El número de pasos sigue siendo inválido.\n");
            return p;
        }
    }
    if (p.stepSize <= 0) {
        printf("Error: El tamaño del paso debe ser positivo.\n");
        printf("Sugerencia: step size = 0.1\n");
        if (scanf("%f", &p.stepSize) != 1) return p;
        if (p.stepSize <= 0) {
            printf("Error: El tamaño del paso sigue siendo inválido.\n");
            return p;
        }
    }

    return p;    
}

float f(float x, float y){
    // Ejemplo: f(x, y) = x * sqrt(y)
    return x  * sqrt(y);
}

Result RungeKutta(argsInput p, int option){
    float a2;

    if (p.stepSize <= 0.0f || p.numSteps <= 0) {
        printf("Error: h y N deben ser positivos.\n");
        return (Result){0.0f};
    }
    
    switch (option) {
        case HEUN:
            printf("Heun\n");
            a2 = 0.5f;
            break;
        case PUNTO_MEDIO:
            printf("Punto Medio\n");
            a2 = 1.0f;
            break;
        case RALSTON:
            printf("Raltson\n");
            a2 = 2.0f / 3.0f; 
            break;
        default:
            printf("Opcion no valida\n");
            return (Result){0.0f};
    }
    float a1 = 1.0f - a2;
    float q = 1/(2.0f * a2);
    float k1 = f(p.initialX, p.initialY);
    if (!isfinite(k1)) {
        printf("Error: f(x,y) no esta definida en el punto inicial (x=%0.6f, y=%0.6f).\n", p.initialX, p.initialY);
        return (Result){0.0f};
    }
    float x2 = p.initialX + q * p.stepSize;
    float y2 = p.initialY + q * k1 * p.stepSize;
    if (!isfinite(x2) || !isfinite(y2)) {
        printf("Error: Valores intermedios invalidos antes de k2 (x=%0.6f, y=%0.6f).\n", x2, y2);
        return (Result){0.0f};
    }
    float k2 = f(x2, y2);
    if (!isfinite(k2)) {
        printf("Error: f(x,y) no esta definida en el punto intermedio (x=%0.6f, y=%0.6f).\n", x2, y2);
        return (Result){0.0f};
    }
    float y = p.initialY; float x = p.initialX;
    int iteration = p.numSteps;
    while (iteration > 0) {
        float delta = p.stepSize * (a1 * k1 + a2 * k2);
        if (!isfinite(delta)) {
            printf("Error: Desbordamiento o NaN en el incremento (it=%d).\n", p.numSteps - iteration);
            return (Result){0.0f};
        }
        y += delta;
        x += p.stepSize;
        if (!isfinite(x) || !isfinite(y)) {
            printf("Error: Desbordamiento o NaN en el estado (it=%d, x=%0.6f, y=%0.6f).\n", p.numSteps - iteration, x, y);
            return (Result){0.0f};
        }
        k1 = f(x, y);
        if (!isfinite(k1)) {
            printf("Error: f(x,y) no esta definida (it=%d, x=%0.6f, y=%0.6f).\n", p.numSteps - iteration, x, y);
            return (Result){0.0f};
        }
        x2 = x + q * p.stepSize;
        y2 = y + q * k1 * p.stepSize;
        if (!isfinite(x2) || !isfinite(y2)) {
            printf("Error: Valores intermedios invalidos antes de k2 (it=%d, x=%0.6f, y=%0.6f).\n", p.numSteps - iteration, x2, y2);
            return (Result){0.0f};
        }
        k2 = f(x2, y2);
        if (!isfinite(k2)) {
            printf("Error: f(x,y) no esta definida en el punto intermedio (it=%d, x=%0.6f, y=%0.6f).\n", p.numSteps - iteration, x2, y2);
            return (Result){0.0f};
        }
        printf("k1 = %0.6f, k2 = %0.6f, it = %d, x: %0.4f, y: %0.6f\n", k1, k2, p.numSteps - iteration, x, y);
        iteration--;
    }
    Result res = {y};
    
    return res;
}

