/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Pares e Impares ----
------------ 08/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
 
//--- Global Var ---
int N;
int num;
int i;
int cimpar=0;
int endo=0;
float endoimpar=0;
int main()
{
    printf("Ingrese el numero total de elementos  \n");
    scanf("%d",&N); 
    printf("Ingrese %d numeros\n",N);
    for(i=0;i<N;i++){
        
        scanf("%d",&num);
        
        if(num%2==0){
            endo=endo+num;
        }
        else{
            endoimpar=endoimpar+num;
            cimpar++;
        }
    }
    endoimpar=endoimpar/cimpar;
    printf("La suma de los pares es %d\n",endo);
    printf("El promedio de los impares es %f",endoimpar);  
}
