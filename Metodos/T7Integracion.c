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
    float lim_inferior; 
    float lim_superior;
    int num_subinterval; 
} params;

typedef struct { 
    float Integral;
    float *x;
    float *fx;
    float h;
    int num_subinterval;
} Result;


// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10
#define TRAPEZOID 1
#define SIMPSON 2
// --------- Function ---------
params input(void);

float get_a0(float x[], float y[], float a1);
float get_a1(float x[], float y[]);
Result Integral(params p, int option);

float f(float x);

// ----------- Main -----------

int main()
{
    params p = input();

    printf("Como desea integrar?\n1) Trapecio\n2) Simpson\n3) Salir\nOpcion: ");
    int op;
    if (scanf("%d", &op) != 1 || (op < 1  || op > 3)){
        printf("Opcion no valida\n");
        return 1;
    }
    if (op == 1 || op == 2) 
        Integral(p,op);
    else {
        printf("Conste\n");
        return 0;
    }
    return 0;
}

// --------- Functions ---------


params input(void){
    params p = {0, 0, 0};
    int tmp;
    printf("lim inf = ");
    // Validacion 
    if (scanf("%f", &p.lim_inferior) != 1) return p;
    printf("lim sup = ");
    if (scanf("%f", &p.lim_superior) != 1) return p;
    printf("num subintervalos = ");
    if (scanf("%d", &tmp) != 1) return p;
    
    if (tmp % 2 != 0) {
        printf("Error: El número de subintervalos debe ser par.\n");
        printf("Sugerencia: %d, %d\nnum subintervalos = ", tmp - 1, tmp + 1);
        if (scanf("%d", &tmp) != 1) return p;
    }
    p.num_subinterval = tmp;
    return p;    
}

float f(float x){
    // Ejemplo: f(x) = x^3+2x^2-x+1
    return x * x * x + 2*x*x - x + 1;
}

Result Integral(params p, int option){
    float h = (p.lim_superior - p.lim_inferior) / p.num_subinterval;
    float f_inf = f(p.lim_inferior); float f_sup = f(p.lim_superior);
    float x[p.num_subinterval + 1];
    float fx[p.num_subinterval + 1];
    float Integral = 0.0f;
    
    if (option == TRAPEZOID){
        float sum = 0.0f;
        for (int step = 1; step < p.num_subinterval; step++) {
            float xi = p.lim_inferior + step * h;
            x[step] = xi;
            fx[step] = f(xi);
            sum += f(xi);
            printf("%.4f\t%.6f\n", x[step], fx[step]);

        }
        Integral = (h / 2) * (f_inf + 2 * sum + f_sup);
    }
    else if (option == SIMPSON){
        float sum_odd = 0.0f, sum_even = 0.0f;

        for (int step = 1; step < p.num_subinterval; step++) {
            float xi = p.lim_inferior + step * h;
            if (step % 2 == 0) sum_even += f(xi);
            else sum_odd += f(xi);
            
            x[step] = xi;
            fx[step] = f(xi);
        }
        Integral = (h / 3) * (f_inf + 4 * sum_odd + 2 * sum_even + f_sup);
    }
    else 
       Integral = 0.0;
    Result res = {Integral, x, fx, h, p.num_subinterval};
    printf("Integral = %0.6f\n", res.Integral);
    printf("x\tf(x)\n");
    printf("h = %0.4f\n", res.h);

    return res;
}

