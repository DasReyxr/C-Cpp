/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Ejercicio 3 Tiendita ----
------------ 18/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h>
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---
void main(){

//-- Local Var --
//- Int -
float Price,Money_Given,Delta;                                 
printf("Input the price of product: ");             
scanf("%f", &Price);                            
printf("Input the money given: \a");
scanf("%f", &Money_Given); 
Delta = Price-Money_Given;
printf("Your bill is %.2f \n",Delta);            
}
