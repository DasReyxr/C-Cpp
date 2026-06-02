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

float fRaltson(float t, float q, const RLCArgs *args){
    return -(q / (args->L * args->C)) + ((args->E0 / args->L) * sinf(args->omega * t));
}

ResultRaltson RungeKutta(RLCArgs p, int option){
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
            return (ResultRaltson){0.0f, 0.0f, 0.0f};
    }
    float a1 = 1.0f - a2;
    float c = 1.0f / (2.0f * a2);
    float t = p.t0;
    float q = p.q0;
    float dq = p.dq0;
    int iteration = p.numSteps;

    while (iteration > 0) {
        float k1_q = dq;
        float k1_dq = fRaltson(t, q, &p);

        float t2 = t + c * p.stepSize;
        float q2 = q + c * p.stepSize * k1_q;
        float dq2 = dq + c * p.stepSize * k1_dq;

        float k2_q = dq2;
        float k2_dq = fRaltson(t2, q2, &p);

        q += p.stepSize * (a1 * k1_q + a2 * k2_q);
        dq += p.stepSize * (a1 * k1_dq + a2 * k2_dq);
        t += p.stepSize;
        iteration--;
    }
    ResultRaltson res = {t, q, dq};
    
    return res;
}

int RungeKuttaTrace(RLCArgs p, int option, float *tOut, float *qOut, int outCount, ResultRaltson *finalResult){
    if (!tOut || !qOut || outCount <= 0) {
        return 0;
    }

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
            return 0;
    }

    float a1 = 1.0f - a2;
    float c = 1.0f / (2.0f * a2);
    float t = p.t0;
    float q = p.q0;
    float dq = p.dq0;
    int iteration = p.numSteps;
    int outIndex = 0;

    int stride = 1;
    if (outCount > 1 && p.numSteps > 0) {
        stride = p.numSteps / (outCount - 1);
        if (stride < 1) {
            stride = 1;
        }
    }

    tOut[outIndex] = t;
    qOut[outIndex] = q;
    outIndex++;

    for (int step = 0; step < iteration; step++) {
        float k1_q = dq;
        float k1_dq = fRaltson(t, q, &p);

        float t2 = t + c * p.stepSize;
        float q2 = q + c * p.stepSize * k1_q;
        float dq2 = dq + c * p.stepSize * k1_dq;

        float k2_q = dq2;
        float k2_dq = fRaltson(t2, q2, &p);

        q += p.stepSize * (a1 * k1_q + a2 * k2_q);
        dq += p.stepSize * (a1 * k1_dq + a2 * k2_dq);
        t += p.stepSize;

        if (((step + 1) % stride) == 0 && outIndex < outCount) {
            tOut[outIndex] = t;
            qOut[outIndex] = q;
            outIndex++;
        }
    }

    if (outIndex < outCount) {
        tOut[outIndex] = t;
        qOut[outIndex] = q;
        outIndex++;
    }

    if (finalResult) {
        *finalResult = (ResultRaltson){t, q, dq};
    }

    return outIndex;
}

