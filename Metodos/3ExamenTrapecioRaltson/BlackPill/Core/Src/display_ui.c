// display_ui.c
#include <Integral.h>
#include "st7735.h"
#include "fonts.h"
#include "display_ui.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
// RGB888 to RGB565 conversion macro (display-specific format)
#define RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

// Hex color to RGB565 conversion macro  
#define HEX_TO_RGB565(hex) RGB565(((hex >> 16) & 0xFF), ((hex >> 8) & 0xFF), (hex & 0xFF))

// Normal Theme - Dark mode
const ColorTheme THEME_NORMAL = {
    .bg =  HEX_TO_RGB565(0x272727), // #272727
    .title = ST7735_CYAN,
    .primary_text = ST7735_WHITE,
    .secondary_text = HEX_TO_RGB565(0x808080),
    .button = ST7735_GREEN,
    .matrix_cell = HEX_TO_RGB565(0x6496FF),
    .matrix_selected = ST7735_YELLOW,
    .separator = HEX_TO_RGB565(0x606060),
    .highlight = ST7735_MAGENTA,
    .input_bg = HEX_TO_RGB565(0x28283C)
};

// Pink Theme - Soft pink aesthetic based on Python UI
const ColorTheme THEME_PINK = {
    .bg = HEX_TO_RGB565(0xFFD4E8),        // #FFD4E8 - Light pink background
    .title = HEX_TO_RGB565(0xC71585),     // #C71585 - Deep pink for titles
    .primary_text = HEX_TO_RGB565(0x8B4789),  // #8B4789 - Purple text
    .secondary_text = HEX_TO_RGB565(0xD891C9), // #D891C9 - Light purple for hints
    .button = HEX_TO_RGB565(0xFF69B4),    // #FF69B4 - Hot pink for buttons
    .matrix_cell = HEX_TO_RGB565(0xFF69B4),   // #FF69B4 - Hot pink for matrix values
    .matrix_selected = HEX_TO_RGB565(0x8B008B), // #8B008B - Dark magenta for selected (high contrast)
    .separator = HEX_TO_RGB565(0xFFB6D9), // #FFB6D9 - Medium pink for lines
    .highlight = ST7735_MAGENTA, // #FF1493 - Deep pink for highlights
    .input_bg = HEX_TO_RGB565(0xFFF0F8)   // #FFF0F8 - Almost white for input bg
};

// Current theme pointer
ColorTheme currentTheme;        
uint8_t isPinkMode = 0;

// Function to switch theme
void toggleTheme(void) {
    isPinkMode = !isPinkMode;
    currentTheme = isPinkMode ? THEME_PINK: THEME_NORMAL;
}

// Initialize with normal theme
void initTheme(void) {
    currentTheme = THEME_PINK;
    			   //THEME_NORMAL;
    isPinkMode = 1;
    			 //0;
}
// Variables externas
extern UART_HandleTypeDef huart1;

char readchar(void) {
    // Esperar a que haya datos disponibles en el buffer UART
    while ((USART1->SR & USART_SR_RXNE) == 0);
    // Leer el carácter recibido
    return (char)(USART1->DR & 0xFF);
}
float UART_READf(int x, int y) {
    int digits = 0;
    char displayStr[11] = {0}; // Buffer para mostrar el número en la pantalla
    float buffer = 0;
    char ch=0;
    int isReadingFloat = 0; // 0 int 1 float
    int decimalPlaces = 0;
    
    // Clear the input area on screen
    ST7735_FillRectangle(x, y, 80, 10, currentTheme.bg);
    
    while (digits < (int)sizeof(displayStr) - 1) {
        ch = readchar();
        
        // Handle Enter
        if (ch == '\r' || ch == '\n') {
            // Send \r\n to terminal
            HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", 2, 100);
            break;
        }
        
        // Handle Backspace (0x08 or 0x7F)
        if (ch == '\b' || ch == 0x7F) {
            if (digits > 0) {
                digits--;
                // Check if we're deleting the decimal point
                if (displayStr[digits] == '.') {
                    isReadingFloat = 0;
                    decimalPlaces = 0;
                }
                displayStr[digits] = '\0';
                // Clear the display area and redraw
                ST7735_FillRectangle(x, y, 80, 10, currentTheme.bg);
                ST7735_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
                
                // Recalculate buffer
                buffer = 0;
                decimalPlaces = 0;
                isReadingFloat = 0;
                for (int i = 0; i < digits; i++) {
                    if (displayStr[i] == '.') {
                        isReadingFloat = 1;
                    } else if (displayStr[i] >= '0' && displayStr[i] <= '9') {
                        if (!isReadingFloat) {
                            buffer = buffer * 10 + (displayStr[i] - '0');
                        } else {
                            decimalPlaces++;
                            buffer += (displayStr[i] - '0') / pow(10.0f, decimalPlaces);
                        }
                    }
                }
                HAL_UART_Transmit(&huart1, (uint8_t*)"\b", 2, 100);
            }
            continue;
        }
        
        // Handle decimal point
        if (ch == '.' && isReadingFloat == 0) {
            isReadingFloat = 1;
            displayStr[digits] = '.';
            digits++;
            displayStr[digits] = '\0';
            ST7735_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
            continue;
        }
        
        // Handle digits
        if(ch >= '0' && ch <= '9') {
            displayStr[digits] = ch;
            if (!isReadingFloat) {
                buffer = buffer * 10 + (ch - '0');
            } else {
                decimalPlaces++;
                buffer += (ch - '0') / pow(10.0f, decimalPlaces);
            }
            digits++;
            displayStr[digits] = '\0';
            // Display immediately
            ST7735_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        }
    }
    return buffer;
}

void isEnterPressed(void){
    char ch = 0x00;
    while(ch != '\r' && ch != '\n') {
        ch = readchar();
    }
}
int UART_READ(int x, int y) {
    int digits = 0;
    char displayStr[11] = {0}; // Buffer para mostrar el número en la pantalla
    int buffer = 0;
    char ch=0;
    
    // Clear the input area on screen
    ST7735_FillRectangle(x, y, 80, 10, currentTheme.bg);
    
    while (digits < (int)sizeof(displayStr) - 1) {
        ch = readchar();
        
        // Handle Enter
        if (ch == '\r' || ch == '\n') {
            // Send \r\n to terminal
            HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", 2, 100);
            break;
        }
        
        // Handle Backspace (0x08 or 0x7F)
        if (ch == '\b' || ch == 0x7F) {
            if (digits > 0) {
                digits--;
                displayStr[digits] = '\0';
                // Clear the display area and redraw
                ST7735_FillRectangle(x, y, 80, 10, currentTheme.bg);
                ST7735_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
                
                // Recalculate buffer
                buffer = 0;
                for (int i = 0; i < digits; i++) {
                    buffer = buffer * 10 + (displayStr[i] - '0');
                }
            }
            continue;
        }
        
        // Handle digits
        if(ch >= '0' && ch <= '9') {
            buffer = buffer * 10 + (ch - '0');
            displayStr[digits] = ch;
            digits++;
            displayStr[digits] = '\0';
            // Display immediately
            ST7735_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        }
    }
    return buffer;
}

params inputIntegral(void){
    params p = {0, 0, 0};
    ST7735_WriteString(0, 5, "lim_inf = ", Font_7x10, currentTheme.title, currentTheme.bg);
    p.lim_inferior = UART_READf(0, 15);
    ST7735_WriteString(0, 25, "lim_sup = ", Font_7x10, currentTheme.title, currentTheme.bg);
    p.lim_superior = UART_READf(0, 35);
    ST7735_WriteString(0, 45, "num_subintervalos = ", Font_7x10, currentTheme.title, currentTheme.bg);
    p.num_subinterval = UART_READ(0, 55);
    return p;
}


RLC_INPUT inputRLC(void){
    RLC_INPUT input = {0.0f, 10};
    char displayStr[20];
    
    ST7735_FillScreenFast(currentTheme.bg);
    
    // Title
    ST7735_WriteString(15, 5, "RLC Evaluation", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_DrawLine(0, 15, ST7735_WIDTH, 15, currentTheme.separator);
    
    // Info
    ST7735_WriteString(0, 22, "L=2mH, C=100uF", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    ST7735_WriteString(0, 32, "Zeta=0.57", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    // Input polynomial grade
    ST7735_WriteString(0, 48, "Poly Grade: ", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    input.polyGrade = (uint8_t)UART_READ(80, 48);
    
      
    // Input prompt
    ST7735_WriteString(0, 60, "Eval time (s) [0-19]:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    ST7735_WriteString(0, 72, "0.00", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    
    input.evalTime = UART_READf(28,72) * 1e-4f; // Convert microseconds to seconds
    
    return input;
}

void printResult(NEWTONRESULT res, float x) {
    char displayStr[40];
    int i;
    uint16_t y_pixel = 10;
    for (i = 0; i < res.size; i++) {
        snprintf(displayStr, sizeof(displayStr), "a[%d] = %.3E", i, res.coefs[i]);
        ST7735_WriteString(0, y_pixel, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        y_pixel += 10;
        if (y_pixel > 150) {
            break;
        }
    }
    
    isEnterPressed();
    
    // Show evaluation result on clean screen
    ST7735_FillScreenFast(currentTheme.bg);
    ST7735_WriteString(0, 0, "Evaluation Result", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_DrawLine(0, 10, ST7735_WIDTH, 10, currentTheme.separator);
    
    snprintf(displayStr, sizeof(displayStr), "t = %.5f s", x);
    ST7735_WriteString(5, 20, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    
    snprintf(displayStr, sizeof(displayStr), "P(t) = %.6f", res.pointEval);
    ST7735_WriteString(5, 35, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    
    // Show polynomial degree
    snprintf(displayStr, sizeof(displayStr), "Degree: %d", res.size - 1);
    ST7735_WriteString(5, 50, displayStr, Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    // Show number of points used
    snprintf(displayStr, sizeof(displayStr), "Points: %d", res.size);
    ST7735_WriteString(5, 62, displayStr, Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    ST7735_WriteString(0, 108, "Press Enter...", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    isEnterPressed();
}


float* plot(uint16_t n, float wn, float t_end_target){
        ST7735_FillScreenFast(currentTheme.bg);

        // Optimized layout for 160x128 screen
        const uint16_t left = 35;           // Left margin for y-axis label
        const uint16_t right = ST7735_WIDTH - 2;
        const uint16_t top = 15;            // Space for title
        const uint16_t bottom = ST7735_HEIGHT - 12;  // Space for x-axis label
        
        const float dt = (n > 1) ? (t_end_target / (float)(n - 1)) : 0.0f;
        const uint16_t plot_w = right - left;
        const uint16_t plot_h = bottom - top;

        float step;
        float evalinT;
        float *y = (float*)malloc(n * sizeof(float));
        if (!y) return NULL;

        float min_y = 1e9f;
        float max_y = -1e9f;

        // Title
        char title[20];
        snprintf(title, sizeof(title), "H(t) Response");
        ST7735_WriteString(40, 2, title, Font_7x10, currentTheme.title, currentTheme.bg);

        // Plot background area
        ST7735_FillRectangle(left, top, plot_w + 1, plot_h + 1, currentTheme.input_bg);

        // Grid (4x4 for better visibility on small screen)
        for (uint16_t gx = 0; gx <= 4; gx++) {
            uint16_t xg = left + (gx * plot_w) / 4;
            for (uint16_t yy = top; yy <= bottom; yy++) {
                ST7735_DrawPixel(xg, yy, currentTheme.separator);
            }
        }
        for (uint16_t gy = 0; gy <= 4; gy++) {
            uint16_t yg = top + (gy * plot_h) / 4;
            for (uint16_t xx = left; xx <= right; xx++) {
                ST7735_DrawPixel(xx, yg, currentTheme.separator);
            }
        }

        // Axes box
        for (uint16_t xx = left; xx <= right; xx++) {
            ST7735_DrawPixel(xx, top, currentTheme.title);
            ST7735_DrawPixel(xx, bottom, currentTheme.title);
        }
        for (uint16_t yy = top; yy <= bottom; yy++) {
            ST7735_DrawPixel(left, yy, currentTheme.title);
            ST7735_DrawPixel(right, yy, currentTheme.title);
        }

        // First pass: determine range for vertical scaling
        for (uint16_t i = 0; i < n; i++) {
            step = dt * (float)i;
            evalinT = H(step, wn, RLC_ZETA_DEFAULT);
            if (evalinT < min_y) min_y = evalinT;
            if (evalinT > max_y) max_y = evalinT;
        }

        if (min_y > max_y) {
            min_y = 0.0f;
            max_y = 1.0f;
        }

        float pad = 0.08f * (max_y - min_y);
        if (pad < 1e-6f) {
            pad = 1.0f;
        }
        max_y += pad;
        min_y -= pad;

        float range = max_y - min_y;
        if (range < 1e-6f) {
            range = 1.0f;
        }

        // Draw y-axis min/max labels (compact)
        char label[12];
        snprintf(label, sizeof(label), "%.0f", max_y);
        ST7735_WriteString(2, top, label, Font_7x10, currentTheme.secondary_text, currentTheme.bg);
        
        snprintf(label, sizeof(label), "%.0f", min_y);
        ST7735_WriteString(2, bottom - 8, label, Font_7x10, currentTheme.secondary_text, currentTheme.bg);

        // Optional zero axis when visible
        float zero_norm = (0.0f - min_y) / range;
        uint16_t zero_ypix = bottom - (uint16_t)(zero_norm * (float)plot_h);
        if (zero_ypix >= top && zero_ypix <= bottom) {
            for (uint16_t xx = left; xx <= right; xx++) {
                ST7735_DrawPixel(xx, zero_ypix, currentTheme.highlight);
            }
        }

        // Second pass: draw curve and keep first 20 values
        for (uint16_t i = 0; i < n; i++) {
            step = dt * (float)i;
            evalinT = H(step, wn, RLC_ZETA_DEFAULT);
            float norm = (evalinT - min_y) / range;

            uint16_t xpix = left + (uint16_t)(((uint32_t)i * plot_w) / (uint32_t)(n - 1));
            uint16_t ypix = bottom - (uint16_t)(norm * (float)plot_h);
            if (ypix < top) ypix = top;
            if (ypix > bottom) ypix = bottom;
            ST7735_DrawPixel(xpix, ypix, COLOR_BLACK);

            if(i < 20){
                y[i] = evalinT;
            }
        }

        // X-axis label
        
        // Time range annotations
        snprintf(label, sizeof(label), "0");
        ST7735_WriteString(left, 108, label, Font_7x10, currentTheme.secondary_text, currentTheme.bg);
        
        snprintf(label, sizeof(label), "%.3f", t_end_target);
        ST7735_WriteString(right - 28, 110, label, Font_7x10, currentTheme.secondary_text, currentTheme.bg);

        return y;
}
