/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos II ---
-------- 28/02/2026 --------

*/

// ------- Main Library -------
#include "main.h"
#include "NewtonRapson.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------

// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10

// Funcion usada


// --------- Function ---------
float H(float t, float wn, float zeta){
    if (zeta >= 1.0f) {
        return 0.0f;
    }
    float omega_d = sqrtf(1.0f - zeta * zeta);
    float a = expf(-zeta * wn * t);
    float b = sinf(wn * omega_d * t);
    float num = wn * a * b;
    float den = omega_d;
    return num / den;
}


float* linspace(float start, float step, int n) {
    float *arr = (float*)malloc(n * sizeof(float));
    if (!arr) return NULL;
    for (int i = 0; i < n; i++) {
        arr[i] = start + i * step;
    }
    return arr;
}



float* diferencias_divididas(poli p) {
    float *a = malloc((p.grado + 1) * sizeof(float));
    if (!a) return NULL;

    // Primera columna: f[x_i] = y_i
    for (int i = 0; i <= p.grado; i++) {
        a[i] = p.y[i];
    }

    // Columnas de diferencias divididas
    for (int j = 1; j <= p.grado; j++) {
        for (int i = p.grado; i >= j; i--) {
            a[i] = (a[i] - a[i - 1]) / (p.x[i] - p.x[i - j]);
        }
    }
    return a;
}

float evalPol(float x, poli p, float *a){
    float eval = a[p.grado];
    for (int i = p.grado - 1; i >= 0; --i) {
        eval = eval * (x - p.x[i]) + a[i];
    }
    return eval;
}

NEWTONRESULT Newton(poli p, float x){
    float *a = diferencias_divididas(p);
    if (!a) return (NEWTONRESULT){0.0f, NULL, 0};

    float y = evalPol(x, p, a);


    NEWTONRESULT res = {y, a, p.grado + 1};
    
    return res;
}

