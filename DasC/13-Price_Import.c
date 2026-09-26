/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Ejercicio 13 Importation ----
------------ 6/09/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h>
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---
int main()
{

    //-- Local Var --
    float Price_Import, NewPrice;
    //- Int -
    printf("Input first number: ");             
    scanf("%f", &Price_Import);
    if(Price_Import>1500)
        {
            NewPrice = Price_Import* 1.11;
        }       
    else
        {
            NewPrice = Price_Import * 1.08;
        }
    printf("Your price was %.3f, now your price is %.3f",Price_Import,NewPrice);
    return 0;
}
