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


// --------- Function ---------

float f1(float R,RLCFunct IN){
    float L = IN.L;
    float C = IN.C;
    float t = IN.t;
    float q = IN.q;

    float omega = sqrtf(1.0f/(L*C) - (R*R)/(4.0f*L*L));
    float expo  = expf((-0.5f*R*t)/L);
    return expo * cosf(omega*t) - q;
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
    float x_prev = initval; float x_next = 0.0f;
    float ea = 0.0f; int it = 0;

    while (it < limits.max_it) {
        float fx = f1(x_prev, IN); float dfx = df(x_prev, IN);
        if (fabsf(dfx) < PRECISION_VAL) { // Evitar división por cero
            return (RESULT){x_prev, ea, it, 0};
        }
        x_next = x_prev - fx / dfx; // Fórmula de Newton-Raphson
        if (it > 0) {
            if (x_prev != 0.0f)
                ea = fabsf((x_next - x_prev) / x_next) * 100.0f;
            else
                ea = fabsf(x_next - x_prev) * 100.0f;
        }
        if (fabsf(fx) <= limits.tol) { // Si f(x) está cercano a 0, se considera que se ha encontrado una raíz
        	return (RESULT){x_next, ea, it + 1, 1};
        }

        x_prev = x_next;
        it++;
    }

    return (RESULT){x_next, ea, it, 0};

}
