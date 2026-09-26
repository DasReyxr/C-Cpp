/*-------- Orlando Contreras -------
------------- Reyes Das -------------


A la clase de Electrónica I del profesor Gardea asiste un grupo numeroso de alumnos. El profesor Gardea es muy exigente y 
aplica cuatro exámenes durante el semestre. Escribe un programa en C que resuelva lo siguiente:

El promedio de calificaciones de cada alumno.
El promedio del grupo en cada examen.
El examen que tuvo el mayor promedio de calificación.

------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
#include <conio.h>
//--- Global Var ---

struct ALUMNO{
  char ALUMNO[50];
  int ID;
  float PROMEDIO;
  float PROMEDIO_PARCIAL[4];
  float P[4];
};    

int main()
{
    int al, no_parcial;
    int numAlumnos;    
    int cpp =0; //cpp is the elemens in Parcial_Prom
    float saveme;
    int saveme2;
    printf("Buenos dias profesor Gabo, Bienvenido al sistema de E-n-SIIMA Auf Das \n");
    printf("Ingresa numero de alumnos\n");
    scanf("%d",&numAlumnos);
    struct ALUMNO UPA[numAlumnos];
    float Parcial_Prom[4]={0,0,0,0};

    for(al=0;al<numAlumnos;al++){
        printf("Ingresa nombre alumno %d\n",al+1);
            scanf("%s",UPA[al].ALUMNO);
                        fflush(stdin);
        // printf("Ingresa ID Alumno %d\n",al+1);
        //     scanf("%d",&UPA[al].ID);
        for(no_parcial=0;no_parcial<4;no_parcial++){
            printf("Ingresa calificacion parcial %d \n",no_parcial+1);
                scanf("%f",&UPA[al].P[no_parcial]);
            UPA[al].PROMEDIO=UPA[al].P[no_parcial]+UPA[al].PROMEDIO;
            Parcial_Prom[no_parcial]+=UPA[al].P[no_parcial];
        }

             UPA[al].PROMEDIO=UPA[al].PROMEDIO*0.25;
        printf("Promedio de alumno %d es %.2f\n",al+1,UPA[al].PROMEDIO);
    }
    for(no_parcial=0;no_parcial<4;no_parcial++){
            Parcial_Prom[no_parcial]/= numAlumnos;
    }
    
    printf("\nPromedio de cada parcial \nP1 %.2f P2 %.2f P3 %.2f P4 %.2f",Parcial_Prom[0],Parcial_Prom[1],Parcial_Prom[2],Parcial_Prom[3]);
    
    while(cpp<4){
    saveme =Parcial_Prom[cpp]; 
    saveme2 = cpp-1;
        while (saveme2>=0 && Parcial_Prom[saveme2] > saveme)
        {
            Parcial_Prom[saveme2+1] = Parcial_Prom[saveme2];
            saveme2--;         
        }
    Parcial_Prom[saveme2+1] = saveme;
    cpp++;
    }
    printf("\n\n");
    
    for(cpp=0;cpp<4;cpp++){
        if(Parcial_Prom[3]/Parcial_Prom[cpp]==1){
            printf("\nEl maisimo examen es %.2f del %d parcial",Parcial_Prom[3],cpp+1);
        }
    }
    //Impresion
    // for(cpp=0;cpp<4;cpp++){
    //     if (cpp==0)
    //     printf("%.2f",Parcial_Prom[cpp]);
    //     else{
    //         printf(" %.2f",Parcial_Prom[cpp]);

    //     }
    // }

    

    return 0;
}
