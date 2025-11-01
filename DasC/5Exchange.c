/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Ejercicio 5 Exchange ----
------------ 18/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h>
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---
void main(){

//-- Local Var --
//- Int -
float usd,mxn;                                 
printf("Input the money given in dollars: ");             
scanf("%f", &usd);                            
mxn = usd*12.48;
printf("The money is %.2f mxn \n",mxn);            
}
