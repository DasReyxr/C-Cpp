#ifndef RALTSON_H
#define RALTSON_H
#include "main.h"

#define HEUN 1
#define PUNTO_MEDIO 2
#define RALSTON 3


float fRaltson(float t, float q, const RLCArgs *args);
ResultRaltson RungeKutta(RLCArgs p, int option);
int RungeKuttaTrace(RLCArgs p, int option, float *tOut, float *qOut, int outCount, ResultRaltson *finalResult);


#endif // RALTSON_H

