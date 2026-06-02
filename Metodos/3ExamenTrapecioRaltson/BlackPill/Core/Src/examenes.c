#include "UI_Methods.h"
#include "display_ui.h"
#include "fonts.h"
#include "st7735.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include "examenes.h"

INIT initVals = {0, 0.0f};
RLCFunct INRLC;
float* INR;
float x0; // Initial guess for Newton-Raphson
RESULT NEWRSON = {0.0f, 0.0f, 0, 0};

float L = RLC_L_DEFAULT;
float C = RLC_C_DEFAULT;
float x[100];
float evalPoint;
const float t_end_target = 0.010f;

Result integralResult;
const float pi = 3.14159265358979323846f;

uint8_t method = 0;

void examen1(void){
    initVals = inputOptions();
    if(initVals.option == NEWTON) {
      INRLC = inputRLC();
      x0 = getIntervalMiddle(); // Get interval bounds and calculate midpoint
      NEWRSON = NewtonRapson((LIMITS){50,initVals.num_presicion}, INRLC, x0);
      displayResult(NEWRSON, 0, 20);
    }
    if(initVals.option == GAUSS) {
      INR = inputRVal();
          //(100, 200, 300, 400, 500, 600);
      Resistivo(INR);
    }
}



void examen2(void){
  RLC_INPUT rlcInput = inputRLC1();
    evalPoint = rlcInput.evalTime;
    uint16_t plotCount = 100;
    uint8_t polyGrade = rlcInput.polyGrade;
    float zeta = 0.57f;
    float wn = 1.0f / sqrtf(L * C);
    float R = 2.0f * zeta * wn * L;
    float *y = plot(plotCount, wn, t_end_target);
    isEnterPressed();
    float step = 1e-4f;
    float *temp = linspace(0.0f, step, 100);
    if (temp) {
        memcpy(x, temp, 100 * sizeof(float));
        free(temp);
    }
    poli p = {x, y, polyGrade};
    NEWTONRESULT res = Newton(p, evalPoint);

    ST7735_FillScreenFast(currentTheme.bg);
    printResult(res, evalPoint);
    free(y);
    free(res.coefs);
    isEnterPressed();
}
/* USER CODE BEGIN 4 */
float function(float t, void *ctx){
  const functArgs *fArgs = (const functArgs *)ctx;
  float i = fArgs->iMax * sinf(fArgs->omega * t + fArgs->phase);
  return i * i;
}

void examen3(void){
    uint8_t option = inputOptions3();
    if (option == INTEGRAL){
        functArgs fArgs = inputIntegral();
        float T = (2.0f * pi) / fArgs.omega;
        float lim_inferior = 0.0f;
        float lim_superior = T * 0.5f;
        integralResult = Integral((params){lim_inferior, lim_superior,fArgs.num_subinterval}, TRAPEZOID, function, &fArgs);
        float iRMS = sqrtf((2.0f / T) * integralResult.Integral);
        outputIntegral(iRMS, fArgs);
}
    else if (option == RLC){
    
    RLC_UI_INPUT rlcInput = inputRLC3();
    RLCArgs rlcArgs = {
      .L = 1.0f,
      .C = 0.25f,
      .E0 = 1.0f,
      .omega = sqrtf(3.5f),
      .t0 = 0.0f,
      .tEnd = 50.0f,
      .stepSize = 0.1f,
      .q0 = rlcInput.q0,
      .dq0 = rlcInput.dq0,
      .numSteps = (int)(50.0f / 0.1f)
    };

    const int sampleCount = 120;
    float *tSamples = (float*)malloc(sampleCount * sizeof(float));
    float *qSamples = (float*)malloc(sampleCount * sizeof(float));
    ResultRaltson rlcFinal = {0.0f, 0.0f, 0.0f};
    int used = 0;

    if (tSamples && qSamples) {
      used = RungeKuttaTrace(rlcArgs, rlcInput.method, tSamples, qSamples, sampleCount, &rlcFinal);
      if (used > 0) {
        float qMin = qSamples[0];
        float qMax = qSamples[0];
        for (int i = 1; i < used; i++) {
          if (qSamples[i] < qMin) qMin = qSamples[i];
          if (qSamples[i] > qMax) qMax = qSamples[i];
        }
        outputRLCGraph(tSamples, qSamples, used, rlcArgs.tEnd, qMin, qMax, rlcArgs.numSteps, rlcInput.method, &rlcFinal);
      }
    }

    if (tSamples) {
      free(tSamples);
    }
    if (qSamples) {
      free(qSamples);
    }
    }

}
