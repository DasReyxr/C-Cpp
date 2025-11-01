/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ 
¿Dónde estarás?
¿En que otros labios mis caricias dejarás?
Mientras aquí
Cada recuerdo es un martirio para mí  
------
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
//--- Global Var ---
int Total;
int iterative,iterative2;
int num;
int ta=0;
int truorfols;
int position = 0;

int main()
{
     printf("Ingrese la longitu de su arrei\n ");
    scanf("%d",&Total);
    int disarray[Total]; 

    printf("Ingrese los numeros\n ");
    for(iterative=0;iterative<Total;iterative++){
        scanf(" %d",&num);
        disarray[iterative]=num;
    }

    printf("tu arrei es \n[ ");
    for(int i=0;i<Total;i++){
        printf("%d ",disarray[i]);
    }
    printf("]\n");
    
    printf("\nGuskate este numero pero en fa padrino\n ");
    scanf("%d",&num);
    
    
    //Filter Section
    for(iterative2=0;iterative2<Total;iterative2++){
            if(num==disarray[iterative2]){
                printf("posicion {%d}",iterative2+1);
                ta=1;
            }

        }
    if(ta==0){
        printf("nel bro, nosta :c {0}");
        }
}
