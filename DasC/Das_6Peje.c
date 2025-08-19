/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Votaciones Fuerza Morena----
-- No cierto profe no soy moreno --
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
//--- Global Var ---
int N;
int Vot;
int i;
int Dip0,Dip1,Dip2,Dip3,Dip4;
int main()
{
    printf("Ingrese el numero de votaciones\n");
    scanf("%d",&N);
    printf("Ingrese los votos, recuerde EL VOTO ES LIBRE Y SEGURO\n");
    printf("0) Amlo 1)Peje 2)Andres Manuel 3)Penanieto 4)Aguelito\n");
    for(i=0;i<N;i++){
        scanf("%d",&Vot);
        switch(Vot){
            case 0:
                Dip0++;
                break;
            case 1:
                Dip1++;
                break;
            case 2:
                Dip2++;
                break;
            case 3:
                Dip3++;
                break;
            case 4:
                Dip4++;
                break;
        }
    
    }
    printf("\nResultados votaciones\nAmlo 0) %d\nPeje 1) %d \nAndres Manuel 2) %d\nPenanieto 3) %d\nAguelito 4) %d",Dip0,Dip1,Dip2,Dip3,Dip4);
}
