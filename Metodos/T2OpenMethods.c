/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos II ---
-------- 18/02/2026 --------

*/

// ------- Main Library -------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------
typedef struct { 
    float val;
    float error; 
    int it; 
    char success;
} RESULT;

typedef struct {
    float xl;
    float xu;
} INTERVAL;

typedef struct {
    int max_it;
    float tol;
} LIMITS;
// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10

// Funcion usada
// f(x) = Sin(x) - 0.5x^2+3
// f'(x) = Cos(x) - x

// --------- Function ---------
float f(float x){
    return sinf(x) - 0.5f * x * x+3;
    //    return x*x-6*x+1;
}
float df(float x){
    return cosf(x) - x;
    //return 2*x-6;
}

RESULT newton(INTERVAL initvals, LIMITS limits, int secante);
RESULT secante(INTERVAL initvals, LIMITS limits);
// ----------- Main -----------

int main()
{
    printf("La funcion usada sera f(x) = Sin(x) - 0.5x^2\n");

    printf("Que metodo desea usar?\n1) Newton-Raphson\n2) Secante\n3) Salir\nOpcion: ");
    int op;
    if (scanf("%d", &op) != 1 || (op < 1  || op > 3)){
        printf("Opcion no valida\n");
        return 1;
    }
    printf("Ingrese iteraciones personalizadas (0 para Default: 10 MAX): ");
    int tol_op;
    scanf("%d", &tol_op);
    if (tol_op == 0) tol_op = MAX_ITER;

    printf("Ingrese tolerancia personalizadas (0 para Default: 1E-4): ");
    float tol_op2;
    scanf("%f", &tol_op2);
    if (tol_op2 == 0) tol_op2 = PRECISION_VAL;
    LIMITS limits = {tol_op, tol_op2};
    
    RESULT res;
    INTERVAL initval = {0.5f, 1.0f};
    int custom_interval;
    printf("Ingrese x0: ");
    scanf("%f", &initval.xl);
    if(op == 0) // Newton-Raphson, se toma un solo valor inicial
        initval.xu = 0; 
    else{
        printf("Ingrese x1: ");
        scanf("%f", &initval.xu);
    }
    
    if (initval.xl >= initval.xu){
        printf("xl debe ser menor que xu\n");
        return 1;
    }
    
    if (op == 1) 
        res = newton(initval, limits, 0);
    else if (op == 2)
        res = secante(initval, limits);
    else {
        printf("Conste\n");
        return 0;
    }
    
    if(!res.success){
        printf("================================\n");
        printf("============= ERROR ===========\n");
        printf("No se pudo encontrar una raiz con el metodo seleccionado\nSe alcanzo el numero maximo de iteraciones (%d)\nsin converger a una solucion dentro de la tolerancia establecida.\n", MAX_ITER);
        return 1;
    }
    else{
    printf("================================\n");
    printf("La raiz %0.2f se obtuvo con:\n\t %d iteraciones (Max %d) \n\t Error de %0.2f %% (Esperado %0.2e)", res.val, res.it, MAX_ITER, res.error, PRECISION_VAL);
    printf("\n================================\n");
    }
//    getchar();

    
    return 0;
}

// --------- Functions ---------

RESULT newton(INTERVAL initvals, LIMITS limits, int secante){
    float x0 = initvals.xl;
    float x_prev = x0; float x_next = 0.0f;
    float ea = 0.0f;
    int it = 0;

    printf("It.\t| x\t\t| f(x)\t\t| f'(x)\t\t| Error(%%)\n");
    while (it < limits.max_it) {
        float fx = f(x_prev); float dfx = df(x_prev);

        if (fabsf(dfx) < PRECISION_VAL) { // Evitar división por cero
            return (RESULT){x_prev, ea, it, 0};
        }
        if (secante)
            x_next = x_prev - fx * (x_prev - initvals.xu) / (fx - f(initvals.xu)); // Fórmula de la secante
        else
            x_next = x_prev - fx / dfx; // Fórmula de Newton-Raphson
        if (it > 0) {
            if (x_prev != 0.0f)
                ea = fabsf((x_next - x_prev) / x_prev) * 100.0f;
            else
                ea = fabsf(x_next - x_prev) * 100.0f;
        }

        printf("%d\t| %0.4f\t| %0.4f\t| %0.4f\t| %0.2f\n", it + 1, x_next, fx, dfx, ea);

        if (fabsf(fx) <= limits.tol) { // Si f(x) está cercano a 0, se considera que se ha encontrado una raíz
            return (RESULT){x_next, ea, it + 1, 1};
        }

        x_prev = x_next;
        it++;
    }

    return (RESULT){x_next, ea, it, 0};

}
RESULT secante(INTERVAL initvals, LIMITS limits){
    return newton(initvals, limits, 1);
}
