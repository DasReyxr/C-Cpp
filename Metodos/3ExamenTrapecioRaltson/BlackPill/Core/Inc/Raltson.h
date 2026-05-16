#ifndef RALTSON_H
#define RALTSON_H
#include "main.h"

#define HEUN 1
#define PUNTO_MEDIO 2
#define RALSTON 3


float fRaltson(float x, float y);
argsInput input(void);
ResultRaltson RungeKutta(argsInput p, int option);


#endif // RALTSON_H

