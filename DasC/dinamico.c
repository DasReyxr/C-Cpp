/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Votaciones Fuerza Morena  ----
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
//--- Global Var ---
int iterative,iterative2;
int Total;
int guardamesta, guardamesta2;
int main()
{
    
    printf("Cuantoskeres ");
    scanf("%d",&Total);
    int VecTor[Total];
    printf("Ingrese %d numeros\n",Total);

     for(iterative=0;iterative<Total;iterative++){
        
         scanf("%d",&guardamesta); 
         VecTor[iterative]=guardamesta;
         printf("guarda %d \n \n",VecTor[iterative]);        
     }

    
     for(iterative2=0;iterative2<Total;iterative2++){
    
     for(int iterative=0;iterative<Total-1;iterative++){
         if(VecTor[iterative]>VecTor[iterative+1]){
             guardamesta2=VecTor[iterative+1];           //guardamesta2=80
             VecTor[iterative+1]=VecTor[iterative];    //{97,97}
             VecTor[iterative]=guardamesta2;             //{80,97}
         }
     }
     }

    for(iterative=0;iterative<Total;iterative++){
        printf(" %d",VecTor[iterative]);
    }
    
}
