#ifndef ComplexGJ_H
#define ComplexGJ_H

#include <math.h>

#define N_MAX 4

typedef struct {
    float r;
    float i;
} cplx;

/* Basic complex operations */
static inline cplx c_add(cplx a, cplx b) { return (cplx){a.r + b.r, a.i + b.i}; }
static inline cplx c_sub(cplx a, cplx b) { return (cplx){a.r - b.r, a.i - b.i}; }
static inline cplx c_mul(cplx a, cplx b) {
    return (cplx){a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r};
}
static inline cplx c_div(cplx a, cplx b) {
    float den = b.r*b.r + b.i*b.i;
    return (cplx){(a.r*b.r + a.i*b.i)/den, (a.i*b.r - a.r*b.i)/den};
}

/* Solver function prototype */
int solve_complex_system(int n, cplx A[N_MAX][N_MAX], cplx b[N_MAX], cplx x[N_MAX]);

void itoa_simple(int, char*, int*);
void ftoa_for_oled(float f, char* buf, int* index, int digits);

#endif
