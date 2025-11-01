/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Ejercicio 2 Calculadora ----
------------ 18/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h>
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---
void main(){

//-- Local Var --
//- Int -
float a, b;                                 // Define two floating-point variables "a" and "b"
printf("Input first number: ");             // Prompt the user to enter the first number
scanf("%f", &a);                            // The "%f" format specifier is used to read a float value.
printf("Input second number: ");
scanf("%f", &b);                            // The '&b' is the address-of operator, which is used to pass the memory address of 'b' to the scanf function, this allows to modify the value of "b"
printf("%.2f + %.2f = %.2f\n",a,b,a+b);     // The "%.2f" format is used to specify a float number with 2 decimal places while the \n is used to introduce a new line
printf("%.2f - %.2f = %.2f\n",a,b,a-b);     // It is printed in the following order "{a}+{b}={c}", the function printf has two arguments, the first one is the format of the second one
printf("%.2f * %.2f = %.2f",a,b,a*b);       
}
