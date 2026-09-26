// display_ui.c
#include "st7735.h"
#include "fonts.h"
#include "display_ui.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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

uint8_t isEnterPressed(){
    char ch = 0x00;
    while(ch != '\r' && ch != '\n') {
        ch = readchar();
    }
    return ch;
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




poli inputVals(int n_points, int poly_order, float eval_x){
    ST7735_FillScreenFast(currentTheme.bg);
    poli p = {NULL, NULL, poly_order, n_points, eval_x};
    p.x = (float*)malloc((size_t)n_points * sizeof(float));
    p.y = (float*)malloc((size_t)n_points * sizeof(float));
    if (p.x == NULL || p.y == NULL) {
        if (p.x != NULL) {
            free(p.x);
        }
        if (p.y != NULL) {
            free(p.y);
        }
        p.x = NULL;
        p.y = NULL;
        p.n_points = 0;
        ST7735_WriteString(0, 20, "Error memoria", Font_7x10, currentTheme.title, currentTheme.bg);
        return p;
    }

    ST7735_WriteString(0, 10, "Ingrese valores:", Font_7x10, currentTheme.title, currentTheme.bg);

    for (int i = 0; i < p.n_points; i++) {
        int row = i % 6;
        if (i > 0 && row == 0) {
            ST7735_FillScreenFast(currentTheme.bg);
            ST7735_WriteString(0, 10, "Ingrese valores:", Font_7x10, currentTheme.title, currentTheme.bg);
        }
        int y = 30 + row * 16;
        char buffer[20];
        sprintf(buffer, "x[%d]:", i);
        ST7735_WriteString(0, y, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        p.x[i] = UART_READf(35, y);
        
        sprintf(buffer, "y[%d]:", i);
        ST7735_WriteString(80, y, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        p.y[i] = UART_READf(115, y);
    }
    return p;

}

INIT inputOptions(void){
    ST7735_FillScreenFast(currentTheme.bg);
    INIT data = {0, 0.0f, 0, 1, 0.0f};
    ST7735_WriteString(0, 10, "Cifras signif:", Font_7x10, currentTheme.title, currentTheme.bg);
    data.num_presicion = (float)UART_READ(90, 10);
    data.num_presicion = pow(10, -data.num_presicion);
    ST7735_WriteString(0, 25, "No. de puntos:", Font_7x10, currentTheme.title, currentTheme.bg);
    data.n_points = UART_READ(90, 25);

    ST7735_WriteString(0, 40, "x evaluar:", Font_7x10, currentTheme.title, currentTheme.bg);
    data.eval_x = UART_READf(70, 40);

    ST7735_WriteString(0, 55, "Seleccione Regresion:", Font_7x10, currentTheme.title, currentTheme.bg);

    ST7735_WriteString(5, 70, "1) Lineal", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(5, 82, "2) Polinomial", Font_7x10, currentTheme.title, currentTheme.bg);
    data.option = UART_READ(120, 82);

    if (data.option == OPT_POLINOMIAL) {
        ST7735_WriteString(0, 97, "Orden polinomio:", Font_7x10, currentTheme.title, currentTheme.bg);
        data.poly_order = UART_READ(110, 97);
    }

    if (data.n_points < 2) {
        data.n_points = 2;
    }
    if (data.option != OPT_POLINOMIAL) {
        data.poly_order = 1;
    }
    if (data.poly_order < 1) {
        data.poly_order = 1;
    }
    if (data.poly_order + 1 > data.n_points) {
        data.poly_order = data.n_points - 1;
    }

    HAL_Delay(500); // Pequeña pausa para evitar lecturas múltiples

    return data;
}

void PrintRegresionType(float* vals, int count, int option) {
    char buffer[32];
    ST7735_FillScreenFast(currentTheme.bg);

    if(option == OPT_LINEAL) {
        sprintf(buffer, "Lineal y=%.4f+%.4fx", vals[0], vals[1]);
        ST7735_WriteString(0, 10, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        return;
    }

    ST7735_WriteString(0, 10, "Polinomio coef:", Font_7x10, currentTheme.title, currentTheme.bg);
    for (int i = 0; i < count && i < 6; i++) {
        sprintf(buffer, "a%d=%.5f", i, vals[i]);
        ST7735_WriteString(0, 24 + i * 12, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    }
}
