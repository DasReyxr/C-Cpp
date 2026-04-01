/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos II ---
-------- 28/02/2026 --------

*/

// ------- Main Library -------
#include "main.h"
#include "GaussJordan.h"
#include "display_ui.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// ---------- Class ----------

// -------- Variables --------

// Funcion usada


// --------- Function ---------
static float eval_poly(const float* a, int order, float x) {
    float y = 0.0f;
    float x_pow = 1.0f;
    for (int i = 0; i <= order; i++) {
        y += a[i] * x_pow;
        x_pow *= x;
    }
    return y;
}

float get_a0(float x[], float y[], int n, float a1){
    float xprom = 0.0f;
    float yprom = 0.0f;
    for (int i = 0; i < n; i++) {
        xprom += x[i];
        yprom += y[i];
    }
    xprom /= (float)n;
    yprom /= (float)n;

    return yprom - a1 * xprom;
}

float get_a1(float x[], float y[], int n){
    float num = 0.0f, den = 0.0f;
    float sx = 0.0f, sy = 0.0f, sx2 = 0.0f, sxy = 0.0f;

    for (int i = 0; i < n; i++) {
        sx += x[i];
        sy += y[i];
        sx2 += x[i] * x[i];
        sxy += x[i] * y[i];
    }

    num = n * sxy - sx * sy;
    den = n * sx2 - sx * sx;
    if (fabsf(den) < 1e-7f) {
        return 0.0f;
    }
    return num / den;
}

void Lineal(poli p){
    if (p.x == NULL || p.y == NULL || p.n_points < 2) {
        return;
    }

    int n = p.n_points;
    float sx = 0.0f, sy = 0.0f, sx2 = 0.0f, sxy = 0.0f;

    for (int i = 0; i < n; i++) {
        sx += p.x[i];
        sy += p.y[i];
        sx2 += p.x[i] * p.x[i];
        sxy += p.x[i] * p.y[i];
    }

    float a1 = get_a1(p.x, p.y, n);
    float a0 = get_a0(p.x, p.y, n, a1);
    float sse = 0.0f;

    for (int i = 0; i < n; i++) {
        float yhat = a0 + a1 * p.x[i];
        float e = p.y[i] - yhat;
        sse += e * e;
    }

    float coeffs[2] = {a0, a1};
    float y_eval = a0 + a1 * p.eval_x;
    PrintRegresionType(coeffs, 2, OPT_LINEAL);

    printf("\\n--- Regresion Lineal ---\\n");
    printf("n=%d\\n", n);
    printf("Sumatorias: Sx=%f, Sy=%f, Sx2=%f, Sxy=%f\\n", sx, sy, sx2, sxy);
    printf("Modelo: y = %f + %f*x\\n", a0, a1);
    printf("Evaluacion en x=%f -> y=%f\\n", p.eval_x, y_eval);
    printf("Error cuadratico total (SSE)=%f\\n", sse);
}

void Polinomial(poli p){
    if (p.x == NULL || p.y == NULL || p.n_points < 2) {
        return;
    }

    int order = p.grado;
    if (order < 1) {
        order = 1;
    }
    if (order + 1 > p.n_points) {
        order = p.n_points - 1;
    }

    int m = order + 1;
    float *sum_x = (float*)calloc((size_t)(2 * order + 1), sizeof(float));
    float *sum_yx = (float*)calloc((size_t)m, sizeof(float));
    float **A = (float**)malloc((size_t)m * sizeof(float*));
    float *b = (float*)malloc((size_t)m * sizeof(float));

    if (sum_x == NULL || sum_yx == NULL || A == NULL || b == NULL) {
        free(sum_x);
        free(sum_yx);
        free(A);
        free(b);
        return;
    }

    for (int i = 0; i < m; i++) {
        A[i] = (float*)malloc((size_t)m * sizeof(float));
        if (A[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(A[k]);
            }
            free(A);
            free(b);
            free(sum_x);
            free(sum_yx);
            return;
        }
    }

    for (int i = 0; i < p.n_points; i++) {
        float x_pow = 1.0f;
        for (int k = 0; k <= 2 * order; k++) {
            sum_x[k] += x_pow;
            x_pow *= p.x[i];
        }

        x_pow = 1.0f;
        for (int k = 0; k <= order; k++) {
            sum_yx[k] += p.y[i] * x_pow;
            x_pow *= p.x[i];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = sum_x[i + j];
        }
        b[i] = sum_yx[i];
    }

    GaussJordanResult gj;
    gj.size = m;
    gj.matrix = A;
    gj.vector = b;

    float* coeffs = GaussJordan(gj);
    if (coeffs != NULL) {
        float sse = 0.0f;
        for (int i = 0; i < p.n_points; i++) {
            float yhat = eval_poly(coeffs, order, p.x[i]);
            float e = p.y[i] - yhat;
            sse += e * e;
        }
        float y_eval = eval_poly(coeffs, order, p.eval_x);

        PrintRegresionType(coeffs, m, OPT_POLINOMIAL);
        printf("\\n--- Regresion Polinomial ---\\n");
        printf("n puntos=%d, orden=%d\\n", p.n_points, order);
        for (int k = 0; k <= 2 * order; k++) {
            printf("Sx^%d=%f\\n", k, sum_x[k]);
        }
        for (int k = 0; k <= order; k++) {
            printf("Syx^%d=%f\\n", k, sum_yx[k]);
        }
        for (int i = 0; i < m; i++) {
            printf("a%d=%f\\n", i, coeffs[i]);
        }
        printf("Evaluacion en x=%f -> y=%f\\n", p.eval_x, y_eval);
        printf("Error cuadratico total (SSE)=%f\\n", sse);
    }

    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(sum_x);
    free(sum_yx);
}
