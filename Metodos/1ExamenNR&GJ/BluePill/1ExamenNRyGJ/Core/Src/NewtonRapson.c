/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos II ---
-------- 28/02/2026 --------

*/

// ------- Main Library -------
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------

// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10

// Funcion usada
// f(x) = Sin(x) - 0.5x^2+3
// f'(x) = Cos(x) - x

// --------- Function ---------

float f(float R,RLCFunct IN){
    return expf((-0.5*R*IN.t)/IN.L) * cosf(sqrtf(1/(IN.L*IN.C) - powf(R, 2)/(4*powf(IN.L, 2)))*IN.t) - IN.q;
    //    return x*x-6*x+1;
}
float df(float R, RLCFunct IN){

    float L = IN.L;
    float C = IN.C;
    float t = IN.t;

    float omega = sqrtf(1.0f/(L*C) - (R*R)/(4.0f*L*L));
    float expo  = expf((-0.5f*R*t)/L);

    return expo * (
           -(t/(2.0f*L))*cosf(omega*t)
           + (R*t/(4.0f*L*L*omega))*sinf(omega*t)
           );
}

// --------- Functions ---------

RESULT NewtonRapson(LIMITS limits, RLCFunct IN, float initval){
    float x0 = initval;
    float x_prev = x0; float x_next = 0.0f;
    float ea = 0.0f;
    int it = 0;

    //printf("It.\t| x\t\t| f(x)\t\t| f'(x)\t\t| Error(%%)\n");
    while (it < limits.max_it) {
        float fx = f(x_prev, IN); float dfx = df(x_prev, IN);

        if (fabsf(dfx) < PRECISION_VAL) { // Evitar división por cero
            return (RESULT){x_prev, ea, it, 0};
        }
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
