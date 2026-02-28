#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H
#include <stdint.h>

// Funciones de dibujado para cada nivel
void drawLevel0(void);
void drawLevel1(uint8_t colMat, uint8_t rowMat);
void drawLevel2(uint8_t success);

// Función auxiliar para actualización parcial
void updateBufferDisplay(const char* buffer);

#endif // DISPLAY_UI_H