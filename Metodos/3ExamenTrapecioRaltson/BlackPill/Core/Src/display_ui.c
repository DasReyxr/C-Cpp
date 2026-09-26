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
static int g_uart_mirror_enabled = 1;

static void UART_PrintRaw(const char* str) {
    if (!str) {
        return;
    }
    HAL_UART_Transmit(&huart1, (uint8_t*)str, (uint16_t)strlen(str), 100);
}

void UART_PRINT_STR(const char* str) {
    UART_PrintRaw(str);
}

void UART_PRINT_FLOAT(float value, int precision) {
    char buffer[32];
    if (precision < 0) {
        precision = 0;
    } else if (precision > 9) {
        precision = 9;
    }
    snprintf(buffer, sizeof(buffer), "%.*f", precision, value);
    UART_PrintRaw(buffer);
}

void UART_PRINTF(const char* format) {
    UART_PrintRaw(format);
}

void UI_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
    ST7735_WriteString(x, y, str, font, color, bgcolor);
    if (g_uart_mirror_enabled) {
        UART_PRINT_STR(str);
    }
}

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
    g_uart_mirror_enabled = 0;
    
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
                UI_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
                
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
            UI_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
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
            UI_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        }
    }
    g_uart_mirror_enabled = 1;
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
    g_uart_mirror_enabled = 0;
    
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
                UI_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
                
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
            UI_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        }
    }
    g_uart_mirror_enabled = 1;
    return buffer;
}



