#ifndef NEWTON_INTERPOLATION_H
#define NEWTON_INTERPOLATION_H
#include "main.h"

// Funciones de dibujado para cada nivel
#define RLC_ZETA_DEFAULT 0.57f
#define RLC_L_DEFAULT 10e-3f
#define RLC_C_DEFAULT 220e-6f



float H(float t, float wn, float zeta);
float* linspace(float start, float end, int n);

float evalPol(float x, poli p, float *a);
float* diferencias_divididas(poli p);
NEWTONRESULT Newton(poli p, float x);


#endif // NEWTON_RAPHSON_H

