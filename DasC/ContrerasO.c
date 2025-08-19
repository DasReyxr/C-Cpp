/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Examen Insertion Sorting  ----
------------ 25/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
//--- Global Var ---
int iterative,iterative2,jiterative;
int Total;
int guardamesta, guardamesta2;
int main()
{
    
    printf("Cuantoskeres ");
    scanf("%d",&Total);
    int VecTor[Total];
    printf("Ingrese %d numeros\n",Total);

    //Guardado
     for(iterative=0;iterative<Total;iterative++){  
         scanf("%d",&guardamesta); 
         VecTor[iterative]=guardamesta;
         printf("guarda[%d], dato{%d}\n \n",VecTor[iterative],iterative+1);        
     }

    while(iterative2<Total){
        guardamesta2 =VecTor[iterative2]; 
        jiterative = iterative2-1;
            while (jiterative>=0 && VecTor[jiterative] > guardamesta2)
            {
                VecTor[jiterative+1] = VecTor[jiterative];
                jiterative--;         
            }
        VecTor[jiterative+1] = guardamesta2;
        iterative2++;
    }
     
    //Impresion
    for(iterative=0;iterative<Total;iterative++){
        if (iterative==0)
        printf("%d",VecTor[iterative]);
        else{
            printf(" %d",VecTor[iterative]);

        }
    }
    
}
