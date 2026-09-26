/*-------- Orlando Contreras -------
------------- Reyes Das -------------


Escribe un programa que, al recibir como datos 24 números reales que representan las temperaturas registradas en el exterior en un periodo de 24 horas, encuentre, con la ayuda de funciones, la temperatura promedio del día, así como la temperatura máxima y la mínima con el horario en el cual se registraron.

Nota: Tendrás que implementar la siguientes funciones: tempProm, tempMax y tempMin.

------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
//--- Global Var ---

void TEMPPROM(float *,int);
void TEMPMINMAX(float *,int opt,int);

int main()
{
    //float Temps[23]={23.57, 33.12, 28.46, 24.81, 22.35, 37.17, 27.62, 21.49, 38.38, 20.71, 26.93, 32.16, 39.64, 30.42, 34.05, 21.68, 29.37, 20.25, 35.97, 31.48, 20.91, 36.28, 22.06, 39.01};    
    
    int numtemps=24;
    float Temps[numtemps-1];
    printf("Hoy es un dia soleado dame %d temperaturas jeje Auf Das \n",numtemps);
    for(int temp=0;temp<numtemps;temp++){
        printf("%d)",temp+1);
        scanf("%f",&Temps[temp]);
    }
    
    TEMPPROM(Temps,numtemps);
    TEMPMINMAX(Temps,0,numtemps);
    TEMPMINMAX(Temps,1,numtemps);
    
    return 0;
}


void TEMPPROM(float *etemp,int nt){
    float sum = 0;
    float Promedio;
    for(int ti=0;ti<nt;ti++){
        sum+=etemp[ti];
    }
    Promedio=sum/(float)nt;
    printf("Promedio de temperatura del dia de hoy  %0.2f C\n",Promedio);
}


void TEMPMINMAX(float *etemp,int opt,int nt){
    int cpp=1,saveme2;
    float saveme;
    while(cpp<nt){
    saveme =etemp[cpp]; 
    saveme2 = cpp-1;
        while (saveme2>=0 && etemp[saveme2] > saveme)
        {
            etemp[saveme2+1] = etemp[saveme2];
            saveme2--;         
            
        }
    etemp[saveme2+1] = saveme;
    cpp++;
    }

    (opt==1) ? printf("\nLa maisima temperatura es %.2f\n\n",etemp[nt-1]) :printf("\nLa mainima temperatura es %.2f\n\n",etemp[0]);

    // //Impresion
    // for(int iterative=0;iterative<24;iterative++){
    //     if (iterative==0)
    //     printf("%.2f",etemp[iterative]);
    //     else{
    //         printf(" %.2f",etemp[iterative]);

    //     }
    // }
}