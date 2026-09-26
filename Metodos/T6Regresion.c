/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos Vi ---
-------- 06/02/2026 --------
*/

// ------- Main Library -------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------
typedef struct { 
    float *x; 
    float *y;
    int grado; 
} poli;

typedef struct { 
    int size;
    float **matrix; 
    float *vector;
} GaussJordanResult;


// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10
// --------- Function ---------
poli input(void);

float get_a0(float x[], float y[], float a1);
float get_a1(float x[], float y[]);
void GaussJordan(GaussJordanResult gj);


// ----------- Main -----------

int main()
{
    poli p = input();

    printf("Que regresion desea usar?\n1) Lineal\n2) Cuadratica\n3) Salir\nOpcion: ");
    int op;
    if (scanf("%d", &op) != 1 || (op < 1  || op > 3)){
        printf("Opcion no valida\n");
        free(p.x);
        free(p.y);
        return 1;
    }
    float res;
    if (op == 1) 
        Lineal(p);
    else if (op == 2)
        Polinomial(p);
        
    else {
        printf("Conste\n");
        free(p.x);
        free(p.y);
        return 0;
    }
    printf("f(%.4f)=%.4f", x,res);
    free(p.x);
    free(p.y);
    
    return 0;
}

// --------- Functions ---------

float get_a0(float x[], float y[], float a1){
    //average of x
    float xprom, yprom;
    xprom = yprom = 0.0f;
    int n = sizeof(x) / sizeof(float);
    for (int i = 0; i < n; i++) {
        xprom += x[i];
        yprom += y[i];
    }
    xprom /= n; yprom /= n;
    
    return (yprom - a1 * xprom);
}
float get_a1(float x[], float y[]){
    float num = 0.0f, den = 0.0f, xt = 0.0f, yt = 0.0f,xt2 = 0.0f, xy = 0.0f;
    int n = sizeof(x) / sizeof(float);
    for (int i = 0; i < n; i++) {
        xt += x[i]; yt += y[i];
        xt2 += x[i] * x[i];
        xy = x[i] * y[i];
    }

    num = n * xy - xt * yt;
    den = n * xt2 - xt * xt;
    return num / den;
}


float Lineal(poli p, float x){
    float a1 = get_a1(p.x, p.y);
    float a0 = get_a0(p.x, p.y, a1);
    printf("y = %.6f + %.6f * x\n", a0, a1);
}

float Polinomial(poli p){
    float xt = 0.0f, xt2 = 0.0f, xt3 = 0.0f, xt4 = 0.0f;
    float yt = 0.0f, xyt = 0.0f, x2yt = 0.0f;
    GaussJordanResult gj;
    int size;
    float **matrix; 
    float *vector;
    
    int n = sizeof(p.x) / sizeof(float);
    
    for(int i = 0; i < n; i++){
        xt      += p.x[i];
        xt2     += p.x[i] * p.x[i];
        xt3     += p.x[i] * p.x[i] * p.x[i];
        xt4     += p.x[i] * p.x[i] * p.x[i] * p.x[i];
        yt      += p.y[i];
        xyt     += p.x[i] * p.y[i];
        x2yt    += p.x[i] * p.x[i] * p.y[i];
    }
    gj.size = 3;
    gj.vector = {yt, xyt, x2yt};
    gj.matrix = {
        {n, xt, xt2},
        {xt, xt2, xt3},
        {xt2, xt3, xt4}
    };

    GaussJordan(gj);
}



void GaussJordan(GaussJordanResult gj){
    for (int i = 0; i < gj.size; i++) {
        float diag = gj.matrix[i][i];
        if (diag == 0) {
            printf("Error: División por cero en la fila %d\n", i + 1);
            return;
        }
        for (int j = 0; j < gj.size; j++) {
            gj.matrix[i][j] /= diag;
        }
        gj.vector[i] /= diag;
        printf("R%d-> R%d/ %0.2f:\n", i + 1, i + 1, diag);
        printMatrix(gj);
        
        for (int k = 0; k < gj.size; k++) {
            if (k != i) {
                float factor = gj.matrix[k][i];
                printf("R%d-> R%d - %0.2f * R%d:\n", k + 1, k + 1, factor, i + 1);
                for (int j = 0; j < gj.size; j++) {
                    gj.matrix[k][j] -= factor * gj.matrix[i][j];
                }
                gj.vector[k] -= factor * gj.vector[i];
                printMatrix(gj);

            }

        }
        
    }
    
    printf("\n\n======== Resultados ========\n");
    printMatrix(gj);
}
float* diferencias_divididas(poli p) {
    float *a = malloc((p.grado + 1) * sizeof(float));
    if (!a) return NULL;

    // Primera columna: f[x_i] = y_i
    for (int i = 0; i <= p.grado; i++) {
        a[i] = p.y[i];
    }

    // Columnas de diferencias divididas
    for (int j = 1; j <= p.grado; j++) {
        for (int i = p.grado; i >= j; i--) {
            a[i] = (a[i] - a[i - 1]) / (p.x[i] - p.x[i - j]);
        }
    }
    return a;
}

void Newton_tabla_diferencias(poli p){
    int n = p.grado + 1;
    float **tabla = malloc((size_t)n * sizeof(float *));
    if (!tabla) return;

    for (int i = 0; i < n; i++) {
        tabla[i] = malloc((size_t)n * sizeof(float));
        if (!tabla[i]) {
            for (int k = 0; k < i; k++) free(tabla[k]);
            free(tabla);
            return;
        }
        for (int j = 0; j < n; j++) tabla[i][j] = 0.0f;
    }

    for (int i = 0; i < n; i++) {
        tabla[i][0] = p.y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            float den = p.x[i + j] - p.x[i];
            tabla[i][j] = (tabla[i + 1][j - 1] - tabla[i][j - 1]) / den;
        }
    }

    printf("\nTabla de diferencias divididas (Newton):\n");
    printf("i\tx_i\tf[x_i]");
    for (int j = 1; j < n; j++) {
        printf("\tf[%d]", j + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%.4f", i, p.x[i]);
        for (int j = 0; j < n - i; j++) {
            printf("\t%.6f", tabla[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) free(tabla[i]);
    free(tabla);
}

poli input(void){
    poli p = {NULL, NULL, 0};

    printf("n = ");
    // Validacion 
    if (scanf("%d", &p.grado) != 1) return p;
    if (p.grado < 0) p.grado = 0;
    p.grado -= 1; // porque el grado es n-1
    p.x = malloc((p.grado + 1) * sizeof(float));
    p.y = malloc((p.grado + 1) * sizeof(float));
    if (!p.x || !p.y){ perror("malloc"); p.grado = 0; return p; }
    int grado = p.grado;
    while(grado >= 0){
        printf("X%d:", grado);
        scanf("%f", &p.x[grado--]);

    }    
    grado = p.grado;

    while(grado >= 0){
        printf("Y%d:", grado);
        scanf("%f", &p.y[grado--]);
    }    

    return p;    

}

float evalPol(float x, poli p, float *a){
    float eval = 0.0f;
    eval = a[0];
    float prod = 1;
    for(int i=1; i <= p.grado; ++i){
        prod *= (x - p.x[i - 1]);
        eval += a[i] * prod;
    }
    return eval;

}

float Newton(poli p, float x){
    float *a = diferencias_divididas(p);
    if (!a) return NAN;

    Newton_tabla_diferencias(p);
    Newton_print(p, a);
    float y = evalPol(x, p, a);
    printf("Coeficientes de Newton:\n");
    for (int i = 0; i <= p.grado; i++) {
        printf("a[%d] = %.6f\n", i, a[i]);
    }
    printf("Evaluacion: P(%.4f) = %.6f\n", x, y);

    free(a);
    return y;
}

float Lagrange(poli p, float x){
    Lagrange_print(p);
    Lagrange_reporte(p, x);

    float px = 0.0f;
    for (int i = 0; i <= p.grado; i++) {
        float li = 1.0f;
        for (int j = 0; j <= p.grado; j++) {
            if (j == i) continue;
            li *= (x - p.x[j]) / (p.x[i] - p.x[j]);
        }
        px += p.y[i] * li;
    }

    printf("Evaluacion: P(%.4f) = %.6f\n", x, px);
    return px;
}

void Lagrange_print(poli p){
    printf("\nPolinomio de Lagrange (forma simbolica):\n");
    printf("P(x) = ");

    for (int i = 0; i <= p.grado; i++) {
        if (i > 0) printf(" + ");
        printf("(%.4f)", p.y[i]);
        for (int j = 0; j <= p.grado; j++) {
            if (j == i) continue;
            printf("*((x - %.4f)/(%.4f ))", p.x[j], p.x[i]- p.x[j]);
        }
    }
    printf("\n");
}

void Lagrange_reporte(poli p, float x){
    printf("\nReporte de calculos intermedios (Lagrange):\n");
    printf("i\ty_i\tL_i(%.4f)\ty_i*L_i(%.4f)\n", x, x);

    float suma = 0.0f;
    for (int i = 0; i <= p.grado; i++) {
        float li = 1.0f;
        for (int j = 0; j <= p.grado; j++) {
            if (j == i) continue;
            li *= (x - p.x[j]) / (p.x[i] - p.x[j]);
        }
        float termino = p.y[i] * li;
        suma += termino;
        printf("%d\t%.6f\t%.6f\t%.6f\n", i, p.y[i], li, termino);
    }
    printf("Suma de terminos = %.6f\n", suma);
}

void Newton_print(poli p, float *a){
    char MainBuff[512] = "";
    char Buff[256] = "";
    size_t main_len = (size_t)snprintf(MainBuff, sizeof(MainBuff), "%0.4f", a[0]);
    size_t buff_len = 0;
    
    for (int i = 1; i <= p.grado; ++i){
            main_len += (size_t)snprintf(MainBuff + main_len, sizeof(MainBuff) - main_len, " + %0.4f", a[i]);
            buff_len += (size_t)snprintf(Buff + buff_len, sizeof(Buff) - buff_len, "(x - %0.4f)", p.x[i - 1]);
            main_len += (size_t)snprintf(MainBuff + main_len, sizeof(MainBuff) - main_len, "%s", Buff);
        }

    printf("f(x) = %s\n", MainBuff);
 
}