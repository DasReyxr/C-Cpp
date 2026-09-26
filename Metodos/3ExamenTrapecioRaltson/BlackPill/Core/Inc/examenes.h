/*
 * examenes.h
 *
 *  Created on: May 30, 2026
 *      Author: dasre
 */

#ifndef INC_EXAMENES_H_
#define INC_EXAMENES_H_

#include "main.h"
// Primer examen
#include "GaussJordan.h"
#include "NewtonRapson.h"
// Segundo examen
#include "NewtonInterpolation.h"
// Tercer examen
#include "Raltson.h"
#include "Integral.h"


// Primer examen
#define MAX_ITER 10
#define NEWTON 1
#define GAUSS 2

// tercer examen
#define INTEGRAL 1
#define RLC 2
void examen1(void);
void examen2(void);

float function(float t, void *ctx);
void examen3(void);

extern uint8_t method;


#endif /* INC_EXAMENES_H_ */
