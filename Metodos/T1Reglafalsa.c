/*
------ Orlando Reyes ------
--------- Auf Das ---------
--- Metodos Numericos I ---
-------- 06/02/2026 --------
3. Criterio de Parada:  
• Un error absoluto o relativo menor a una tolerancia predefinida (por ejemplo, 10−6) o Un número máximo de iteraciones para evitar bucles infinitos.  
4. Menú Interactivo:  
• El programa deberá presentar un menú al inicio con las siguientes opciones:  
1) Ejecutar el Método de la Bisección.   2) Ejecutar el Método de la Regla Falsa.  3) Salir del programa.  
5. Salida del Programa:  
• Independientemente del método seleccionado, el programa deberá mostrar:  
o La aproximación de la raíz encontrada. o El número de iteraciones realizadas.  
o La tolerancia utilizada.  
o Opcionalmente, se puede presentar una tabla resumen con los valores de los 
extremos, el punto medio (o la estimación de la raíz en el caso de la regla falsa) 
y el valor de 𝑓(𝑥) en cada iteración.  

dudas con jp
es lo mismo ea q si multiplico los numeros y m da uno tikito
*/

// ------- Main Library -------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------- Class ----------
typedef struct { 
    float *coef; 
    int grado; 
} poli;

typedef struct { 
    float val;
    float error; 
    int it; 
    char success;
} RESULT;

typedef struct {
    float xl;
    float xu;
} INTERVAL;

typedef struct {
    int max_it;
    float tol;
} LIMITS;
// -------- Variables --------
#define PRECISION_VAL 0.0001f
#define MAX_ITER 10
// --------- Function ---------
poli input(void);
float evalPol(float x, poli p);
RESULT biseccion(poli p, INTERVAL initvals, LIMITS limits);
RESULT biseccion_flag(poli p, INTERVAL initvals, LIMITS limits, int reglafalsa);

RESULT regla(poli p, INTERVAL initvals,LIMITS limits);

// ----------- Main -----------

int main()
{
    poli p = input();

    //float val = evalPol(10, p);
    printf("Que metodo desea usar?\n1) Biseccion\n2) Regla Falsa\n3) Salir\nOpcion: ");
    int op;
    if (scanf("%d", &op) != 1 || (op < 1  || op > 3)){
        printf("Opcion no valida\n");
        free(p.coef);
        return 1;
    }
    printf("Ingrese iteraciones personalizadas (0 para Default: 10 MAX): ");
    int tol_op;
    scanf("%d", &tol_op);
    if (tol_op == 0) tol_op = MAX_ITER;

    printf("Ingrese tolerancia personalizadas (0 para Default: 1E-4): ");
    float tol_op2;
    scanf("%f", &tol_op2);
    if (tol_op2 == 0) tol_op2 = PRECISION_VAL;
    LIMITS limits = {tol_op, tol_op2};
    
    RESULT res;
    INTERVAL initval = {0.5f, 1.0f};
    int custom_interval;
    printf("Ingrese xl: ");
    scanf("%f", &initval.xl);
    printf("Ingrese xu: ");
    scanf("%f", &initval.xu);
    if (initval.xl >= initval.xu){
        printf("xl debe ser menor que xu\n");
        free(p.coef);
        return 1;
    }
    
    if (op == 1) 
        res = biseccion(p, initval, limits);
    else if (op == 2)
        res = regla(p, initval, limits);
    else {
        printf("Conste\n");
        free(p.coef);
        return 0;
    }
    
    if(!res.success){
        printf("================================\n");
        printf("============= ERROR ===========\n");
        printf("No se pudo encontrar una raiz con el metodo de la regla falsa\nSe alcanzo el numero maximo de iteraciones (%d)\nsin converger a una solucion dentro de la tolerancia establecida.\n", MAX_ITER);
        free(p.coef);
        return 1;
    }
    else{
    printf("================================\n");
    printf("La raiz %0.4f se obtuvo con:\n\t %d iteraciones (Max %d) \n\t Error de %0.2f %% (Esperado %0.2e)", res.val, res.it, MAX_ITER, res.error, PRECISION_VAL);
    printf("\n================================\n");
    }
//    getchar();

    
    free(p.coef);
    return 0;
}

// --------- Functions ---------
poli input(void){
    poli p = {NULL, 0};

    printf("Grado del polinomio: ");
    // Validacion 
    if (scanf("%d", &p.grado) != 1) return p;
    if (p.grado < 0) p.grado = 0;

    p.coef = malloc((p.grado + 1) * sizeof(float));
    if (!p.coef){ perror("malloc"); p.grado = 0; return p; }
    int grado = p.grado;
    while(grado >= 0){
        printf("X%d:", grado);
        scanf("%f", &p.coef[grado--]);

    }    
    return p;    

}

float evalPol(float x, poli p){
    float eval = 0.0f;
    for (int i = p.grado; i >= 0; --i){
        eval += p.coef[i] * powf(x, i);
    }
    return eval;

}
RESULT biseccion(poli p, INTERVAL initvals, LIMITS limits){
    return biseccion_flag(p, initvals, limits, 0);
}

RESULT biseccion_flag(poli fx, INTERVAL initvals, LIMITS limits, int reglafalsa){
    float xl = initvals.xl; float xu = initvals.xu;
    float xr = 0.0f; float xr_prev = 0.0f;
    float fxl = evalPol(xl, fx);
    float fxu = evalPol(xu, fx);
    int it = 0; float ea = 0.0f;


    if (fxl == 0.0f) return (RESULT){xl, 0, 0, 1};
    if (fxu == 0.0f) return (RESULT){xu, 0, 0, 1};
    if (fxl * fxu > 0.0f) return (RESULT){0, 0, 0, 0}; // no hay cambio de signo
    printf("It.\t| xl\t\t| xu\t\t| xr\t\t| f(xr)\t\t| Error(%%)\n");
    while (it < limits.max_it) {
        if (reglafalsa) xr = xu - evalPol(xu, fx) * (xu - xl) / (evalPol(xu, fx) - evalPol(xl, fx)); 
        else  xr = 0.5f * (xl + xu); 

        if (it == 0)
            ea = 0.0f;
        else {
            if (xr_prev != 0.0f)
                ea = fabsf((xr - xr_prev) / xr_prev) * 100.0f;
            else
                ea = fabsf(xr - xr_prev) * 100.0f;
        }
        
        float fxr = evalPol(xr, fx);
        if (fabsf(fxr) <= PRECISION_VAL)  // Si f(xr) está cercano a 0, se considera que se ha encontrado una raíz
            return (RESULT){xr, ea, it + 1, 1};
        else if (fxl * fxr < 0.0f)
            xu = xr, fxu = fxr;
        else
            xl = xr, fxl = fxr;
        printf("%d\t| %0.4f\t| %0.4f\t| %0.4f\t| %0.4f\t| %0.2f\n", it + 1, xl, xu, xr, fxr, ea);
        xr_prev = xr;
        it++;
    }

    return (RESULT){xr, ea, (int)it, 0};
}

RESULT regla(poli fx, INTERVAL initvals, LIMITS limits){
    return biseccion_flag(fx, initvals, limits, 1);}