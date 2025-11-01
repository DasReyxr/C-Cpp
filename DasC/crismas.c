#include <stdio.h>

int main()
{//declaración de variables//
int matAl, carrEs, semAl;
float promedio;
//Solicitar datosd del alumno//
printf ("ingrese la matAl del alumno ");
scanf ("%d", &matAl);
printf ("\ningrese la promedio del alumno ");
scanf ("%f", &promedio);
printf ("Ingrese el semAl del alumno ");
scanf ("%d", &semAl);
printf ("\ningrese la carrEs del alumno \n 1) Industrial \n 2) Telemática \n 3) Computación \n 4) Mecánica \n");
scanf ("%d", &carrEs);
return 0;
}