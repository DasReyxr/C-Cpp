#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H
#include <stdint.h>
#include "main.h"

// Funciones de dibujado para cada nivel
void drawLevel0(void);
void drawLevel1(uint8_t colMat, uint8_t rowMat);
void drawLevel2(uint8_t success);

// Función auxiliar para actualización parcial
void updateBufferDisplay(const char* buffer);

char readchar(void);
float UART_READf(int x, int y);
int UART_READ(int x, int y);
INIT inputOptions(void);
RLCFunct inputRLC(void);
#endif // DISPLAY_UI_H