/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos II ---
-------- 28/02/2026 --------

*/

// ------- Main Library -------
#include "main.h"
#include "Integral.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------

// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10

// Funcion usada


// --------- Function ---------

float f(float x){
    // Ejemplo: f(x) = x^3+2x^2-x+1
    return x * x * x + 2*x*x - x + 1;
}

Result Integral(params p, int option, Integrand func, void *ctx){
    float h = (p.lim_superior - p.lim_inferior) / p.num_subinterval;
    float f_inf = func(p.lim_inferior, ctx); float f_sup = func(p.lim_superior, ctx);
    float *x = (float*)malloc((p.num_subinterval + 1) * sizeof(float));
    float *fx = (float*)malloc((p.num_subinterval + 1) * sizeof(float));
    float Integral = 0.0f;
    
    if (option == TRAPEZOID){
        float sum = 0.0f;
        for (int step = 1; step < p.num_subinterval; step++) {
            float xi = p.lim_inferior + step * h;
            x[step] = xi;
            fx[step] = func(xi, ctx);
            sum += func(xi, ctx);

        }
        Integral = (h / 2) * (f_inf + 2 * sum + f_sup);
    }
    else if (option == SIMPSON){
        float sum_odd = 0.0f, sum_even = 0.0f;

        for (int step = 1; step < p.num_subinterval; step++) {
            float xi = p.lim_inferior + step * h;
            if (step % 2 == 0) sum_even += func(xi, ctx);
            else sum_odd += func(xi, ctx);
            
            x[step] = xi;
            fx[step] = func(xi, ctx);
        }
        Integral = (h / 3) * (f_inf + 4 * sum_odd + 2 * sum_even + f_sup);
    }
    else 
       Integral = 0.0;
    Result res = {Integral, x, fx, h, p.num_subinterval};

    return res;
}

