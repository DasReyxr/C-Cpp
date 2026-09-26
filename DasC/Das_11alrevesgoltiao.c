/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ 
Alreves goltiao
------
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
#include <string.h>
//--- Global Var ---
char tring[100];
char tringvoltiadajeje[100];

int iterative,iterative2;
int position;
int letra;
int ta=0;
int saizo;
int main()
{
    printf("Inversor de texto Auf Das \n");
    printf("Ingresa la cadena que gustes\n");
    gets(tring);
    saizo = strlen(tring);
    // //Printing Section
    for(iterative2=strlen(tring)-1;iterative2>=0;iterative2--){
        printf("%c",tring[iterative2]);
     }
    return 0;
}
