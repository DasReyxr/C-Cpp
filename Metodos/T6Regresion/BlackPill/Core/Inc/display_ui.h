#ifndef DISPLAY_UI_H
#define DISPLAY_UI_H
#include <stdint.h>
#include "main.h"

// Color Theme Structure
typedef struct {
    uint16_t bg;
    uint16_t title;
    uint16_t primary_text;
    uint16_t secondary_text;
    uint16_t button;
    uint16_t matrix_cell;
    uint16_t matrix_selected;
    uint16_t separator;
    uint16_t highlight;
    uint16_t input_bg;
} ColorTheme;


// Current theme (defined in display_ui.c)
extern ColorTheme currentTheme;


// Funciones de dibujado para cada nivel
void drawLevel0(void);
void drawLevel1(uint8_t colMat, uint8_t rowMat);
void drawLevel2(uint8_t success);

// Función auxiliar para actualización parcial
void updateBufferDisplay(const char* buffer);
void initTheme(void);
char readchar(void);
float UART_READf(int x, int y);
int UART_READ(int x, int y);
INIT inputOptions(void);

poli inputVals(int n_points, int poly_order, float eval_x);

void PrintRegresionType(float* vals, int count, int option);
#endif // DISPLAY_UI_H
