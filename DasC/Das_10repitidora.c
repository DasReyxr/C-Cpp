/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ 
Ascii 30H->0 48d->0 
------
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
#include <string.h>
#include <ctype.h>
//--- Global Var ---
char tring[100];
int iterative, jterative;
int num,letra;
int lenghtof;

int main()
{
    printf("Repetidor de litras Auf Das \n");
    printf("Ingresa la cadena que gustes en formato xAyB siendo X numeros\n");
    gets(tring);
    lenghtof=strlen(tring);
 
    //Filter Section
    for(iterative=0;iterative<lenghtof;iterative++){
            if(isdigit(tring[iterative])){
                num = tring[iterative];
                num = num -48;
                letra=tring[iterative+1];
                
                for(jterative=0; jterative<num;jterative++){
                    printf("%c",letra);
                }
            }
        
        }

    return 0;
}
