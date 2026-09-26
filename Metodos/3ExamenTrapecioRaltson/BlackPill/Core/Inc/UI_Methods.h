/*
 * UI_Methods.h
 *
 *  Created on: May 30, 2026
 *      Author: dasre
 */

#ifndef INC_UI_METHODS_H_
#define INC_UI_METHODS_H_

// Primer examen
#include "GaussJordan.h"
#include "NewtonRapson.h"
// Segundo examen
#include "NewtonInterpolation.h"
// Tercer examen
#include "Raltson.h"
#include "Integral.h"
#include "main.h"
#include "display_ui.h"

// 1 Examen
uint8_t inputMethod(void);
INIT inputOptions(void);
RLCFunct inputRLC(void);
RLC_INPUT inputRLC1(void);
float getIntervalMiddle(void);
float* inputRVal(void);
void displayResult(RESULT res, int x, int y);

// 2 Examen 
float* plot(uint16_t n, float wn, float t_end_target);
void printResult(NEWTONRESULT res, float x);

// 3 Examen
uint8_t inputOptions3(void);

functArgs inputIntegral(void);
void outputIntegral(float integralVal, functArgs fArgs);

RLC_UI_INPUT inputRLC3(void);
void outputRLCGraph(const float *t, const float *q, int count, float tEnd, float qMin, float qMax, int iterations, int method, const ResultRaltson *result);




#endif /* INC_UI_METHODS_H_ */
