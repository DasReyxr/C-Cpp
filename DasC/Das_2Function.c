/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Switch Activity ----
------------ 08/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
 
//--- Global Var ---
float x;
int main()
{
        printf("Input x\n");
        scanf("%f",&x);                                                          
        if(x<=50)
        {
            if(x>25)
            {
                x=x*x+(x*x*x-18);
                printf("Caso 3) %f",x);
            }
            else
            {
                if(x>11)
                {
                    x=x*x*x-12;
                    printf("Caso 2) %f",x);
                }
                else
                {
                    x=(4/x)-x;
                    printf("Caso 1) %f",x);
                }
            }
        }
        else 
        {
            printf("0");
        }

}
