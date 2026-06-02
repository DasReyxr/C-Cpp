#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H
#include "main.h"

// Funciones de dibujado para cada nivel
float f(float R,RLCFunct IN);
float df(float R, RLCFunct IN);
RESULT NewtonRapson(LIMITS limits, RLCFunct IN, float initval);

#endif // DISPLAY_UI_H
