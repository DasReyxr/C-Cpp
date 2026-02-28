// display_ui.c
#include "st7735.h"
#include "fonts.h"
#include "display_ui.h"
#include <string.h>
#include <stdio.h>
// RGB888 to RGB565 conversion macro (display-specific format)
#define RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

// Hex color to RGB565 conversion macro  
#define HEX_TO_RGB565(hex) RGB565(((hex >> 16) & 0xFF), ((hex >> 8) & 0xFF), (hex & 0xFF))

// Color Theme Structure - Descriptive names based on usage
typedef struct {
    uint16_t bg;              // Background color
    uint16_t title;           // Title/header text
    uint16_t primary_text;    // Primary text color
    uint16_t secondary_text;  // Secondary/hint text
    uint16_t button;          // Button/action color
    uint16_t matrix_cell;     // Matrix cell values
    uint16_t matrix_selected; // Selected matrix cell
    uint16_t separator;       // Lines and separators
    uint16_t highlight;       // Navigation/editing mode highlight
    uint16_t input_bg;        // Input/selected background
} ColorTheme;

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
    currentTheme = //THEME_PINK;
    			   THEME_NORMAL;
    isPinkMode = //1;
    			 0;
}
// Variables externas



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
    while(digits<11 || ch == 0x0D) { 
        
        ch = readchar();
        if (ch == '.' && isReadingFloat == 0) {
            isReadingFloat = 1; // Cambiar a estado de punto decimal
            displayStr[digits] = '.'; // Mostrar el punto en la pantalla    
        }
        if(ch >= '0' && ch <= '9') {
            buffer = buffer * 10 + (ch - '0');
            displayStr[digits] = ch; // Mostrar el carácter en la pantalla    
            if (isReadingFloat) 
                buffer /= 10.0f;
            digits++;
            }
        
    }
    displayStr[digits] = '\0'; // Null-terminate the string
    ST7735_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    return buffer;
}

int UART_READ(int x, int y) {
    int digits = 0;
    char displayStr[11] = {0}; // Buffer para mostrar el número en la pantalla
    float buffer = 0;
    char ch=0;
    while(digits<11 || ch == 0x0D) {         
        ch = readchar();
        if(ch >= '0' && ch <= '9') {
            buffer = buffer * 10 + (ch - '0');
            displayStr[digits] = ch; // Mostrar el carácter en la pantalla    
            digits++;
        }
    }
    displayStr[digits] = '\0'; // Null-terminate the string
    ST7735_WriteString(x, y, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    return buffer;
}
INIT inputOptions(void){
    ST7735_FillScreenFast(currentTheme.bg);
    INIT data;
    // Título
    ST7735_WriteString(30, 10, "Ingrese numero de cifras significativas:", Font_7x10, currentTheme.title, currentTheme.bg);
    data.num_presicion = UART_READ(30,20); // Enter
    ST7735_WriteString(30, 30, "1) Circuito RLC:", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(30, 40, "2) Circuito Resistivo:", Font_7x10, currentTheme.title, currentTheme.bg);
    data.option = UART_READ(30, 50); // Enter
    
    return data;
}

RLCFunct inputRLC(void){
    RLCFunct data;
    ST7735_FillScreenFast(currentTheme.bg);
    // Título
    ST7735_WriteString(30, 10, "Ingrese los valores del circuito RLC", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(30, 20, "Capacitancia (C):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.C = UART_READf(30,30); // Enter
    ST7735_WriteString(30, 40, "Inductancia (L):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.L = UART_READf(30,50); // Enter
    ST7735_WriteString(30, 60, "Disipacion Carga (q/q0):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.q = UART_READf(30,70); // Enter
    ST7735_WriteString(30, 80, "Tiempo (t):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.t = UART_READf(30,90); // Enter
    
    return data;
}



