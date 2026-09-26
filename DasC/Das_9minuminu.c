/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ 
Ascii 0d97-122
------
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
//--- Global Var ---
char tring[100];
char lowcase[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int iterative;
int position;
int letra;
int ta=0;
int main()
{
    printf("Detector de minusculas Auf Das \n");
    printf("Ingresa la cadena que gustes\n");
    gets(tring);
    printf("\nIngresa la posicion a buscar\n ");
    scanf("%d",&position);    
    //Filter Section
    for(iterative=0;iterative<sizeof(lowcase);iterative++){
            if(tring[position-1]==lowcase[iterative]){
                printf("La letra en la posicion {%d} Si es minuscula '%c'",position,tring[position-1]);
                ta=1;
            }
        }

    if(ta==0){
        printf("nel bro, la letra en la posicion {%d} no es minuscula '%c' :c",position,tring[position-1]);
        }
    return 0;
}
