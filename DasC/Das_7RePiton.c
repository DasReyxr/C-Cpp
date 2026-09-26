/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------
Y yo sali repiton
En serio, me la pase repite y repite
Mira *buuuuuuuuurp*
----
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
//--- Global Var ---
int Total;
int iterative,iterative2;
int num;
int truorfols;
int position = 0;

int main()
{
    printf("'Yo sali re-Piton' (Jr Peluche,2012) \nIngrese el numero de elementos\n");
    scanf("%d",&Total);
    int array_repi[Total]; 
        
    //Fill the array of 0's
    for(int i=0;i<Total;i++){
         array_repi[i]=0;
     }

    //Save data
    printf("Ingrese los numeros\n");
    for(iterative=0;iterative<Total;iterative++){

        truorfols=0;
        scanf("%d",&num);
        
        //Filter Section
        for(iterative2=0;iterative2<Total;iterative2++){
                if(num==array_repi[iterative2]){
                    truorfols=1;
                }
            }
        
        if(truorfols==0){
            array_repi[position]=num;
            position++;
        }

    }
    
     //Printing Section
     for(int i=0;i<Total;i++){
         printf(" %d",array_repi[i]);
     }
}
