/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos II ---
-------- 28/02/2026 --------

*/

// ------- Main Library -------
#include "main.h"
#include "Raltson.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------

// -------- Variables --------


// --------- Function ---------
float fRaltson(float x, float y){
    // Ejemplo: f(x, y) = x * sqrt(y)
    return x  * sqrt(y);
}

ResultRaltson RungeKutta(argsInput p, int option){
    float a2;

    
    switch (option) {
        case HEUN:
            a2 = 0.5f;
            break;
        case PUNTO_MEDIO:
            a2 = 1.0f;
            break;
        case RALSTON:
            a2 = 2.0f / 3.0f; 
            break;
        default:
            return (ResultRaltson){0.0f};
    }
    float a1 = 1.0f - a2;
    float q = 1/(2.0f * a2);
    float k1 = fRaltson(p.initialX, p.initialY);

    float x2 = p.initialX + q * p.stepSize;
    float y2 = p.initialY + q * k1 * p.stepSize;

    float k2 = fRaltson(x2, y2);

    float y = p.initialY; float x = p.initialX;
    int iteration = p.numSteps;
    while (iteration > 0) {
        float delta = p.stepSize * (a1 * k1 + a2 * k2);
        y += delta;
        x += p.stepSize;

        k1 = fRaltson(x, y);

        x2 = x + q * p.stepSize;
        y2 = y + q * k1 * p.stepSize;
        k2 = fRaltson(x2, y2);
        iteration--;
    }
    ResultRaltson res = {y};
    
    return res;
}

