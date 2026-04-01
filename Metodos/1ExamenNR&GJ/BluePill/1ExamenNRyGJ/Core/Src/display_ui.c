// display_ui.c
#include "st7735.h"
#include "fonts.h"
#include "main.h"
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
extern uint8_t matSize;
extern cplx A[N_MAX][N_MAX];
extern cplx b[N_MAX];
extern cplx x[N_MAX];
extern char buffer[16];
extern uint8_t index_Var;
extern uint8_t editingReal;
extern uint8_t navigating;

typedef struct{
  int option;
  int num_presicion;
} INIT;

typedef struct {
    float C;
    float L;
    float q;
    float t;
} RLCFunct;

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




void drawLevel0(void) {
    ST7735_FillScreenFast(currentTheme.bg);
    
    // Título
    ST7735_WriteString(30, 10, "INGRESE TAMANO", Font_7x10, currentTheme.title, currentTheme.bg);
    
    // Mostrar buffer con cursor
    char displayStr[20];
    if(index_Var == 0) {
        sprintf(displayStr, "Sistema: _");
    } else {
        sprintf(displayStr, "Sistema: %s", buffer);
    }
    ST7735_WriteString(45, 40, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    
    // Rango válido
    ST7735_WriteString(45, 70, "Rango: 2-4", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    // Instrucciones
    ST7735_WriteString(20, 88,  "[S+P] C. Tema", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    ST7735_WriteString(20, 100, "[0-9] Numero", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    ST7735_WriteString(20, 112, "[ = ] Confirmar", Font_7x10, currentTheme.button, currentTheme.bg);
    if (navigating) {
        ST7735_FillRectangle(148, 110, 10, 12, currentTheme.input_bg);
        ST7735_WriteString(150, 112, "S", Font_7x10, currentTheme.highlight, currentTheme.input_bg);
    }
}

// ==================== LEVEL 1: Ingreso de coeficientes ====================
void drawLevel1(uint8_t colMat, uint8_t rowMat) {
    ST7735_FillScreenFast(currentTheme.bg);
    
    // Título
    char title[24];
    sprintf(title, "DATOS %dx%d", matSize, matSize);
    ST7735_WriteString(10, 2, title, Font_7x10, currentTheme.title, currentTheme.bg);
    
    // Calcular espaciado
    int cellWidth = 22;
    int startX = 8;
    int startY = 16;
    int rowHeight = 12;
    
    // Dibujar matriz aumentada [A|b]
    for(uint8_t i = 0; i < matSize; i++) {
        int y = startY + i * rowHeight;
        
        // Coeficientes de A
        for(uint8_t j = 0; j < matSize; j++) {
            int x = startX + j * cellWidth;
            
            // Determinar si esta celda está seleccionada
            uint8_t isSelected = (i == colMat && j == rowMat);
            uint16_t color = isSelected ? currentTheme.matrix_selected : currentTheme.matrix_cell;
            uint16_t bgColor = isSelected ? currentTheme.input_bg : currentTheme.bg;
            
            // Convertir número a string (solo parte real para matriz compacta)
            char numStr[8];
            int idx = 0;
            ftoa_for_oled(A[i][j].r, numStr, &idx, 1);
            numStr[idx] = '\0';
            
            // Dibujar rectángulo de selección
            if(isSelected) {
                ST7735_FillRectangle(x-1, y-1, cellWidth-2, 11, bgColor);
            }
            
            ST7735_WriteString(x, y, numStr, Font_7x10, color, bgColor);
        }
        
        // Separador |
        int sepX = startX + matSize * cellWidth;
        ST7735_WriteString(sepX, y, "|", Font_7x10, currentTheme.separator, currentTheme.bg);
        
        // Vector b (constantes)
        int bX = sepX + 10;
        uint8_t isConstSelected = (i == colMat && rowMat == matSize);
        uint16_t bColor = isConstSelected ? currentTheme.matrix_selected : currentTheme.button;
        uint16_t bBgColor = isConstSelected ? currentTheme.input_bg : currentTheme.bg;
        
        char bStr[8];
        int idx = 0;
        ftoa_for_oled(b[i].r, bStr, &idx, 1);
        bStr[idx] = '\0';
        
        if(isConstSelected) {
            ST7735_FillRectangle(bX-1, y-1, cellWidth-2, 11, bBgColor);
        }
        
        ST7735_WriteString(bX, y, bStr, Font_7x10, bColor, bBgColor);
    }
    
    // Panel de edición en la parte inferior
    int panelY = startY + matSize * rowHeight + 8;
    
    // Línea separadora
    ST7735_FillRectangle(0, panelY - 2, 128, 1, currentTheme.separator);
    
    // Mostrar posición actual
    char posStr[24];

    if(rowMat < matSize) {
        sprintf(posStr, "A[%d][%d]", colMat + 1, rowMat + 1);
    } else {
        sprintf(posStr, "b[%d]", colMat + 1);
    }
    ST7735_WriteString(0, panelY, posStr, Font_7x10, currentTheme.title, currentTheme.bg);
    
    // Mostrar qué parte se está editando
    panelY += 12;
    char realStr[16];
    char imagStr[16];
    
    if(navigating){
    	if(rowMat < matSize){
		sprintf(realStr, "Real %.4f", A[colMat][rowMat].r);
		sprintf(imagStr, "Imag j%.4f", A[colMat][rowMat].i);
		}
    	else{
    		sprintf(realStr, "Real %.4f", b[colMat].r);
			sprintf(imagStr, "Imag j%.4f", b[colMat].i);
    	}
    	ST7735_WriteString(70, panelY-12, "READ", Font_7x10, currentTheme.highlight, currentTheme.bg);
        ST7735_WriteString(0, panelY, realStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        ST7735_WriteString(0, panelY+10, imagStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        ST7735_WriteString(50, panelY+24, "[WASD] Mov", Font_7x10, currentTheme.highlight, currentTheme.bg);
    }
    else {
        if (editingReal) {
            // Editing real part: show buffer as real, imag as last entered
            if (index_Var == 0) {
                sprintf(realStr, "Real %.4f", (rowMat < matSize) ? A[colMat][rowMat].r : b[colMat].r);
            } else {
                sprintf(realStr, "Real %s", buffer);
            }
            ST7735_WriteString(120, panelY, "<<", Font_7x10, currentTheme.button, currentTheme.bg);
            sprintf(imagStr, "Imag j%.4f", (rowMat < matSize) ? A[colMat][rowMat].i : b[colMat].i);

        } else {
            // Editing imaginary part
            sprintf(realStr, "Real %.4f", (rowMat < matSize) ? A[colMat][rowMat].r : b[colMat].r);
            
            if (index_Var == 0) {
                sprintf(imagStr, "Imag j%.4f", (rowMat < matSize) ? A[colMat][rowMat].i : b[colMat].i);
            } else {
                sprintf(imagStr, "Imag j%s", buffer);
            }
            ST7735_WriteString(120, panelY+10, "<<", Font_7x10, currentTheme.button, currentTheme.bg);
        }
        ST7735_WriteString(70, panelY-12, "WRITE", Font_7x10, currentTheme.matrix_selected, currentTheme.bg);
        ST7735_WriteString(0, panelY, realStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        ST7735_WriteString(0, panelY+10, imagStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    }
    
    // Controles en la parte más baja
    ST7735_WriteString(0, panelY+24, "[=]OK", Font_7x10, currentTheme.button, currentTheme.bg);

    if(isPinkMode)
    ST7735_DrawImage(120, panelY+14, 30, 30, (uint16_t*)IE8BITPK);
    else
    ST7735_DrawImage(120, panelY+14, 30, 30, (uint16_t*)IE8BITBK);
                                                

}

// ==================== LEVEL 2: Resultados ====================
void drawLevel2(uint8_t success) {
    ST7735_FillScreenFast(currentTheme.bg);
    
    if(success) {
        // Título
        ST7735_WriteString(45, 5, "SOLUCION:", Font_7x10, currentTheme.title, currentTheme.bg);
        
        int startY = 20;
        int rowHeight = 16;
        
        // Mostrar cada solución
        for(uint8_t i = 0; i < matSize; i++) {
            int y = startY + i * rowHeight;
            
            // Variable (xi =)
            uint8_t posy = 8;
            char varStr[20];
            // Valor (parte real)
            char realStr[20];
            int idx = 0;
            char imagStr[2];
            // Parte imaginaria
            if(x[i].i != 0.0f) {
                
                int idx = 0;
                if(x[i].i > 0) {
                    imagStr[idx++] = '+';
                }

                imagStr[idx++] = 'j';                
                sprintf(varStr, "x%d = %.2f %s%.2f", i + 1,x[i].r,imagStr,x[i].i);
            }
            else sprintf(varStr, "x%d = %.2f", i + 1, x[i].r);
                      

            ST7735_WriteString(8, y, varStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);             

            y+=15;
        }
        
        // Instrucciones
        int instrY = startY + matSize * rowHeight + 10;
        ST7735_WriteString(10, instrY, "Presione [T] para", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
        ST7735_WriteString(10, instrY + 10, "nuevo sistema", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
        
    } else {
        // Error: sistema sin solución
        ST7735_WriteString(20, 40, "SISTEMA SIN", Font_7x10, ST7735_RED, currentTheme.bg);
        ST7735_WriteString(25, 55, "SOLUCION", Font_7x10, ST7735_RED, currentTheme.bg);
        ST7735_WriteString(15, 80, "Matriz singular", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
        ST7735_WriteString(10, 100, "Presione [T]", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
        ST7735_WriteString(10, 110, "para reintentar", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    }
}

// Función auxiliar: Limpiar solo el área del buffer (actualización parcial)
void updateBufferDisplay(const char* buffer) {
    // Borrar área anterior
    ST7735_FillRectangle(60, 90, 60, 10, currentTheme.bg);
    // Escribir nuevo buffer
    ST7735_WriteString(60, 90, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
}
