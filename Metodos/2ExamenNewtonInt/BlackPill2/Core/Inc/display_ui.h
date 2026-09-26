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

// RLC Evaluation Input Structure
typedef struct {
    float evalTime;      // Evaluation time in seconds
    uint8_t polyGrade;   // Polynomial grade (degree)
} RLC_INPUT;

// ---- COLORS ----
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_CYAN    0x07ff
#define COLOR_MAGENTA 0xF81F
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_PINK    0xFC18
#define COLOR_PURPLE  0x8010
#define COLOR_ORANGE  0xFD20




// Current theme (defined in display_ui.c)
extern ColorTheme currentTheme;


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
void displayResult(RESULT res, int x, int y);
void isEnterPressed(void);



// --- Funciones específicas para cada ejercicio ---
RLC_INPUT inputRLC(void);

float* plot(uint16_t n, float wn, float t_end_target);
void printResult(NEWTONRESULT res, float x);

#endif // DISPLAY_UI_H