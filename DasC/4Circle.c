/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Ejercicio 4 Circle ----
------------ 18/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h>
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---
void main(){

//-- Local Var --
//- Int -
const float PI= 3.14159;
float radius,area,circunference,pir;                                 
printf("Input the radius of circle: ");             
scanf("%f", &radius);                            
pir= PI*radius;
area=pir*radius;
circunference=2*pir;
printf("The area is %.4f and the circunference %.4f \n",area,circunference);            
}
