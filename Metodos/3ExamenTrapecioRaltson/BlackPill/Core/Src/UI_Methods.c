// display_ui.c
#include <Integral.h>
#include "st7735.h"
#include "fonts.h"
#include "display_ui.h"
#include "UI_Methods.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

uint8_t inputMethod(void){
    ST7735_FillScreenFast(currentTheme.bg);
    uint8_t yPos = 10;
    uint8_t method = 0;
    ST7735_WriteString(0, yPos, "q examen qiere ", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(0, yPos += 10, "1) Ecuaciones Lineales y no Lineales ", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(0, yPos += 10, "2) Interpolacion", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(0, yPos += 10, "3) Integrales y EDOs", Font_7x10, currentTheme.title, currentTheme.bg);
    method = (uint8_t)UART_READ(0, yPos += 10);
    return method;
}


// Examen 1

INIT inputOptions(void){
    ST7735_FillScreenFast(currentTheme.bg);
    INIT data = {0,0.0};
    // Título
    ST7735_WriteString(0, 10, "Ingrese # de cifras significativas:", Font_7x10, currentTheme.title, currentTheme.bg);
    data.num_presicion = UART_READ(5,30); // Enter
    data.num_presicion = pow(10, -data.num_presicion);
    ST7735_WriteString(0, 40, "Seleccione Circuito a resolver:", Font_7x10, currentTheme.title, currentTheme.bg);

    ST7735_WriteString(5, 60, "1) RLC:", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(5, 70, "2) Resistivo:", Font_7x10, currentTheme.title, currentTheme.bg);
    data.option = UART_READ(5, 80); // Enter
    HAL_Delay(500); // Pequeña pausa para evitar lecturas múltiples

    return data;
}

uint8_t inputOptions3(void){
    ST7735_FillScreenFast(currentTheme.bg);
    ST7735_WriteString(0, 10, "Q qiere hacer otrabes:", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(5, 20, "1) Irms:", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(5, 30, "2) RLC:", Font_7x10, currentTheme.title, currentTheme.bg);
    uint8_t option = UART_READ(5, 80); // Enter
    HAL_Delay(500); // Pequeña pausa para evitar lecturas múltiples

    return option;
}

RLCFunct inputRLC(void){
    RLCFunct data;
    ST7735_FillScreenFast(currentTheme.bg);
    // Título
    ST7735_WriteString(0, 5, "Ingrese los valores:", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(0, 20, "Capacitancia (C):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.C = UART_READf(30,30); // Enter
    ST7735_WriteString(0, 40, "Inductancia (L):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.L = UART_READf(30,50); // Enter
    ST7735_WriteString(0, 60, "Factor de Dis. Carga (q/q0):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.q = UART_READf(30,70); // Enter
    ST7735_WriteString(0, 90, "Tiempo (t):", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data.t = UART_READf(50,90); // Enter
    
    return data;

}

float getIntervalMiddle(void){
    float a;
    ST7735_FillScreenFast(currentTheme.bg);
    ST7735_WriteString(0, 5, "Intervalo de busqueda", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(0, 20, "Limite inferior:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    a = UART_READf(30,30);
    
    // Calculate and display midpoint    
    HAL_Delay(1000); // Brief pause to show the calculated value
    return a;
}

float* inputRVal(void){
    static float data[7] = {0};
    ST7735_FillScreenFast(currentTheme.bg);
    // Título
    ST7735_WriteString(0, 5, "Ingrese los valores:", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_WriteString(0, 20, "R1:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data[0] = UART_READf(30,20); // Enter

    ST7735_WriteString(0, 30, "R2:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data[1] = UART_READf(30,30); // Enter
    ST7735_WriteString(0, 40, "R3:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data[2] = UART_READf(30,40); // Enter
    ST7735_WriteString(0, 50, "R4:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data[3] = UART_READf(30,50); // Enter
    ST7735_WriteString(0, 60, "R5:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data[4] = UART_READf(30,60); // Enter
    ST7735_WriteString(0, 70, "R6:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data[5] = UART_READf(30,70); // Enter
    ST7735_WriteString(0, 80, "VCC:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    data[6] = UART_READf(30,80); // Enter
    
    return data;
}


void displayResult(RESULT res, int x, int y) {
    ST7735_FillScreenFast(currentTheme.bg);

	char buffer[50];
    sprintf(buffer, "Resultado: %.6f", res.val);
    ST7735_WriteString(x, y, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    sprintf(buffer, "Error: %.2f%%", res.error);
    ST7735_WriteString(x, y + 20, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    sprintf(buffer, "Iteraciones: %d", res.it);
    ST7735_WriteString(x, y + 30, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    sprintf(buffer, "Convergencia: %s", res.success ? "Si" : "No");
    ST7735_WriteString(x, y + 40, buffer, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    ST7735_WriteString(5, 120, "Presione Enter...", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    // Wait for Enter key
    char ch;
    do {
        ch = readchar();
    } while (ch != '\r' && ch != '\n');

}


// Examen 2

poli inputPOLI(void){
    poli p = {NULL, NULL, 0};
    char displayStr[20];
    ST7735_WriteString(0, 5, "n = ", Font_7x10, currentTheme.title, currentTheme.bg);
    p.grado = UART_READf(0,20)-1; // Enter
    p.x = malloc((p.grado + 1) * sizeof(float));
    p.y = malloc((p.grado + 1) * sizeof(float));
    


    return p;    


}


RLC_INPUT inputRLC1(void){
    RLC_INPUT input = {0.0f, 10};
    char displayStr[20];
    
    ST7735_FillScreenFast(currentTheme.bg);
    
    // Title
    ST7735_WriteString(15, 5, "RLC Evaluation", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_DrawLine(0, 15, ST7735_WIDTH, 15, currentTheme.separator);
    
    // Info
    ST7735_WriteString(0, 22, "L=10mH, C=220uF", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
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
        static float y[100];
        if (n == 0) {
            return NULL;
        }
        if (n > 100) {
            n = 100;
        }
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
        float min_y = 1e9f;
        float max_y = -1e9f;

        // Title
        char title[20];
        snprintf(title, sizeof(title), "Step Response");
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

            y[i] = evalinT;
        }

        // X-axis label
        
        // Time range annotations
        snprintf(label, sizeof(label), "0");
        ST7735_WriteString(left, 108, label, Font_7x10, currentTheme.secondary_text, currentTheme.bg);
        
        snprintf(label, sizeof(label), "%.3f", t_end_target);
        ST7735_WriteString(right - 28, 110, label, Font_7x10, currentTheme.secondary_text, currentTheme.bg);

        return y;
}


// Examen 3
functArgs inputIntegral(void){
    functArgs fArgs = {0, 0, 0};    
    ST7735_FillScreenFast(currentTheme.bg);
    UI_WriteString(0, 5, "Omega = ", Font_7x10, currentTheme.title, currentTheme.bg);
    
    fArgs.omega = UART_READf(0, 15);
    UI_WriteString(0, 25, "Phase = ", Font_7x10, currentTheme.title, currentTheme.bg);
    fArgs.phase = UART_READf(0, 35);
    UI_WriteString(0, 45, "imax = ", Font_7x10, currentTheme.title, currentTheme.bg);
    fArgs.iMax = UART_READf(0, 55);
    UI_WriteString(0, 65, "num_subintervalos = ", Font_7x10, currentTheme.title, currentTheme.bg);
    fArgs.num_subinterval = UART_READ(0, 75);
    return fArgs;
}

void outputIntegral(float integralVal, functArgs fArgs){
    ST7735_FillScreenFast(currentTheme.bg);
    char displayStr[40];
    float yPos = 10;
    snprintf(displayStr, sizeof(displayStr), "%.1f sin(%.1ft + %.1f)", fArgs.iMax, fArgs.omega, fArgs.phase);

    UI_WriteString(45, yPos, "i(t) = ", Font_7x10, currentTheme.title, currentTheme.bg);
    UI_WriteString(0, yPos+=10, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);

    snprintf(displayStr, sizeof(displayStr), "IRMS = %.5f", integralVal);    
    UI_WriteString(0, yPos+=20, displayStr, Font_7x10, currentTheme.title, currentTheme.bg);    
    snprintf(displayStr, sizeof(displayStr), "con %d subintervalos", fArgs.num_subinterval);    
    UI_WriteString(0, yPos+=10, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);

    isEnterPressed();
}

RLC_UI_INPUT inputRLC3(void){
    RLC_UI_INPUT input = {0.0f, 0.0f, 3};
    ST7735_FillScreenFast(currentTheme.bg);

    UI_WriteString(0, 0, "RLC Input", Font_7x10, currentTheme.title, currentTheme.bg);
    //UI_WriteString(0, 12, "q0 =", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    //input.q0 = UART_READf(35, 12);

    //UI_WriteString(0, 26, "dq0 =", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    //input.dq0 = UART_READf(35, 26);
    // initial conditions on 0
    input.q0 = 0.0f;
    input.dq0 = 0.0f;

    UI_WriteString(0, 10, "Metodo", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    UI_WriteString(0, 20, "1 Heun", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    UI_WriteString(0, 30, "2 Punto Medio", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    UI_WriteString(0, 40, "3 Raltson", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    input.method = (uint8_t)UART_READ(0, 52);
    if (input.method < 1 || input.method > 3) {
        input.method = 3;
    }

    UI_WriteString(0, 66, "L=1 C=0.25 E0=1", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    UI_WriteString(0, 78, "w=sqrt(3.5)", Font_7x10, currentTheme.secondary_text, currentTheme.bg);

    return input;
}

void outputRLCGraph(const float *t, const float *q, int count, float tEnd, float qMin, float qMax, int iterations, int method, const ResultRaltson *result){
    if (!t || !q || count <= 1 || !result) {
        return;
    }

    const char *methodStr = "R";
    if (method == 1) {
        methodStr = "H";
    } else if (method == 2) {
        methodStr = "PM";
    }

    if (qMax - qMin < 1e-6f) {
        qMax = qMin + 1.0f;
    }

    ST7735_FillScreenFast(currentTheme.bg);

    char displayStr[40];

    const int x0 = 18;
    const int y0 = 118;
    const int x1 = 155;
    const int y1 = 32;

    ST7735_DrawLine(x0, y0, x1, y0, currentTheme.separator);
    ST7735_DrawLine(x0, y0, x0, y1, currentTheme.separator);

    float xScale = (float)(x1 - x0) / tEnd;
    float yScale = (float)(y0 - y1) / (qMax - qMin);

    int prevX = x0;
    int prevY = y0 - (int)((q[0] - qMin) * yScale);
    for (int i = 1; i < count; i++) {
        int xi = x0 + (int)(t[i] * xScale);
        int yi = y0 - (int)((q[i] - qMin) * yScale);
        if (xi < x0) xi = x0;
        if (xi > x1) xi = x1;
        if (yi < y1) yi = y1;
        if (yi > y0) yi = y0;
        ST7735_DrawLine(prevX, prevY, xi, yi, currentTheme.highlight);
        prevX = xi;
        prevY = yi;
    }

    UI_WriteString(0, 108, "Press Enter...", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    isEnterPressed();

    if (tEnd <= 0.0f) {
        return;
    }

    ST7735_FillScreenFast(currentTheme.bg);

    UI_WriteString(0, 0, "Solucion analitica", Font_7x10, currentTheme.title, currentTheme.bg);
    snprintf(displayStr, sizeof(displayStr), "t:0..%.1f", tEnd);
    UI_WriteString(0, 12, displayStr, Font_7x10, currentTheme.secondary_text, currentTheme.bg);

    float qMinAnalytic = -1.8708f * sinf(2.0f * t[0]) + 2.0f * sinf(1.8708f * t[0]);
    float qMaxAnalytic = qMinAnalytic;
    for (int i = 1; i < count; i++) {
        float qi = -1.8708f * sinf(2.0f * t[i]) + 2.0f * sinf(1.8708f * t[i]);
        if (qi < qMinAnalytic) qMinAnalytic = qi;
        if (qi > qMaxAnalytic) qMaxAnalytic = qi;
    }

    if (qMaxAnalytic - qMinAnalytic < 1e-6f) {
        qMaxAnalytic = qMinAnalytic + 1.0f;
    }

    const int x0a = 18;
    const int y0a = 118;
    const int x1a = 155;
    const int y1a = 32;

    ST7735_DrawLine(x0a, y0a, x1a, y0a, currentTheme.separator);
    ST7735_DrawLine(x0a, y0a, x0a, y1a, currentTheme.separator);

    xScale = (float)(x1a - x0a) / tEnd;
    yScale = (float)(y0a - y1a) / (qMaxAnalytic - qMinAnalytic);

    float q0a = -1.8708f * sinf(2.0f * t[0]) + 2.0f * sinf(1.8708f * t[0]);
    prevX = x0a;
    prevY = y0a - (int)((q0a - qMinAnalytic) * yScale);
    for (int i = 1; i < count; i++) {
        float qi = -1.8708f * sinf(2.0f * t[i]) + 2.0f * sinf(1.8708f * t[i]);
        int xi = x0a + (int)(t[i] * xScale);
        int yi = y0a - (int)((qi - qMinAnalytic) * yScale);
        if (xi < x0a) xi = x0a;
        if (xi > x1a) xi = x1a;
        if (yi < y1a) yi = y1a;
        if (yi > y0a) yi = y0a;
        ST7735_DrawLine(prevX, prevY, xi, yi, currentTheme.highlight);
        prevX = xi;
        prevY = yi;
    }

    UI_WriteString(0, 108, "Press Enter...", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    isEnterPressed();
}

// RLC_INPUT inputRLC(void){
//     RLC_INPUT input = {0.0f, 10};
//     char displayStr[20];
    
//     ST7735_FillScreenFast(currentTheme.bg);
    
//     // Title
//     ST7735_WriteString(15, 5, "RLC Evaluation", Font_7x10, currentTheme.title, currentTheme.bg);
//     ST7735_DrawLine(0, 15, ST7735_WIDTH, 15, currentTheme.separator);
    
//     // Info
//     ST7735_WriteString(0, 22, "L=2mH, C=100uF", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
//     ST7735_WriteString(0, 32, "Zeta=0.57", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
//     // Input polynomial grade
//     ST7735_WriteString(0, 48, "Poly Grade: ", Font_7x10, currentTheme.primary_text, currentTheme.bg);
//     input.polyGrade = (uint8_t)UART_READ(80, 48);
    
      
//     // Input prompt
//     ST7735_WriteString(0, 60, "Eval time (s) [0-19]:", Font_7x10, currentTheme.primary_text, currentTheme.bg);
//     ST7735_WriteString(0, 72, "0.00", Font_7x10, currentTheme.primary_text, currentTheme.bg);
    
//     input.evalTime = UART_READf(28,72) * 1e-4f; // Convert microseconds to seconds
    
//     return input;
// }
/*
void printResult(NEWTONRESULT res, float x) {
    char displayStr[40];
    int i;
    uint16_t y_pixel = 10;
    for (i = 0; i < res.size; i++) {
        snprintf(displayStr, sizeof(displayStr), "a[%d] = %.3E", i, res.coefs[i]);
        UI_WriteString(0, y_pixel, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
        y_pixel += 10;
        if (y_pixel > 150) {
            break;
        }
    }
    
    isEnterPressed();
    
    // Show evaluation result on clean screen
    ST7735_FillScreenFast(currentTheme.bg);
    UI_WriteString(0, 0, "Evaluation Result", Font_7x10, currentTheme.title, currentTheme.bg);
    ST7735_DrawLine(0, 10, ST7735_WIDTH, 10, currentTheme.separator);
    
    snprintf(displayStr, sizeof(displayStr), "t = %.5f s", x);
    UI_WriteString(5, 20, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    
    snprintf(displayStr, sizeof(displayStr), "P(t) = %.6f", res.pointEval);
    UI_WriteString(5, 35, displayStr, Font_7x10, currentTheme.primary_text, currentTheme.bg);
    
    // Show polynomial degree
    snprintf(displayStr, sizeof(displayStr), "Degree: %d", res.size - 1);
    UI_WriteString(5, 50, displayStr, Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    // Show number of points used
    snprintf(displayStr, sizeof(displayStr), "Points: %d", res.size);
    UI_WriteString(5, 62, displayStr, Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    
    UI_WriteString(0, 108, "Press Enter...", Font_7x10, currentTheme.secondary_text, currentTheme.bg);
    isEnterPressed();
}

*/
