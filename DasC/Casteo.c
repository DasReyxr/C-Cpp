/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Putchar Casteo ----
-- Casting is convert one datatype to another -
------------ 30/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h>
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
int main()
{
    int res;
    char a = 'A';
    char b = 'B';
    char c = '2';

    res = a + b - c;                                  // res=A+B-C    =    res=65+66-50  /   /*Esto en codigo ascii/
    printf("El Resultado es: %d", res);
    printf("\n");
    printf("El Resultado es: %c", res);
    return 0;
}