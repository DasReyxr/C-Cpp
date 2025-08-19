/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Calificaciones  ----
------------ 19011/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output

//--- Global Var ---
int N;
int Cal;
int i;
int range1,range2,range3,range4,range5;
int main()
{
    printf("Ingrese el numero de calificaciones\n");
    scanf("%d",&N);
    printf("Ingrese la calificacion\n");
    for(i=0;i<N;i++){

        scanf("%d",&Cal);
        if(Cal>10){
            printf("Oilooilo");
            }
        else{
            if(Cal>8.99)
                range5++;
            else{
                if(Cal>7.99)
                    range4++;
                else{
                    if(Cal>5.99)
                        range3++;
                        else{
                            if(Cal>3.99)
                                range2++;
                                else{
                                    if(Cal>0)
                                        range1++;
                                }
                        }
                    }
                }
            }

      }
            printf("Rangos 0-3.99) %d \nRango 4-5.99) %d \nRango 6-7.99 %d\nRango 8-8.99) %d\nRango 9-10) %d ",range1,range2,range3,range4,range5);
}
