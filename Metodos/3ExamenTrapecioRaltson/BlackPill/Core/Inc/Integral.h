#ifndef INTEGRAL_H
#define INTEGRAL_H
#include "main.h"

// Funciones de dibujado para cada nivel
#define RLC_ZETA_DEFAULT 0.57f
#define RLC_L_DEFAULT 10e-3f
#define RLC_C_DEFAULT 220e-6f
#define TRAPEZOID 1
#define SIMPSON 2

float f3(float x);

Result Integral(params p, int option, Integrand func, void *ctx);

#endif // INTEGRAL_H

