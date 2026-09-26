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
//--- Global Var ---

struct ALUMNO {
  char ALUMNO[50];
  int ID;
  float PROMEDIO;
  float PROMEDIO_PARCIAL[4];
  float P[4];
};    

void CAPTURADO(struct ALUMNO *,int);
void PROMEDIO_AL(struct ALUMNO *);
void PROMEDIO_PAR(struct ALUMNO *,int,float *);
void MAXIMA_CAL(float *);
int main()
{
    int numAlumnos;    

    printf("Buenos dias profesor Gabo, Bienvenido al sistema de E-n-SIIMA Auf Das \n");
    printf("Ingresa numero de alumnos\n");
    scanf("%d",&numAlumnos);
    float Parcial_Prom[4] = {0,0,0,0};
    struct ALUMNO UPA[numAlumnos];

    for(int al=0;al<numAlumnos;al++){
        CAPTURADO(&UPA[al],al);
        
        PROMEDIO_AL(&UPA[al]);
    }
    
    PROMEDIO_PAR(UPA,numAlumnos,Parcial_Prom);
    printf("\nPromedio de cada parcial \nP1 %.2f P2 %.2f P3 %.2f P4 %.2f",Parcial_Prom[0],Parcial_Prom[1],Parcial_Prom[2],Parcial_Prom[3]);
    MAXIMA_CAL(Parcial_Prom);
    return 0;
}

void CAPTURADO(struct ALUMNO *UNI,int al){
    printf("Ingresa nombre alumno %d\n",al+1);
        scanf("%s",UNI->ALUMNO);
        
    printf("Ingresa ID Alumno %d\nAL",al+1);
        scanf("%d",&UNI->ID);
    
    for(int no_parcial=0;no_parcial<4;no_parcial++){
        printf("Ingresa calificacion parcial %d\n",no_parcial+1);
            scanf("%f",&UNI->P[no_parcial]);
    }
}

void PROMEDIO_AL(struct ALUMNO *UNI){
    float sum = 0;

    for(int no_parcial=0;no_parcial<4;no_parcial++){
        
        sum+=UNI->P[no_parcial];
    }

    UNI->PROMEDIO=sum/4.0;
    printf("Promedio de %s es %.2f\n",UNI->ALUMNO,UNI->PROMEDIO);
}



void PROMEDIO_PAR(struct ALUMNO *UNI,int numAlumnos,float *PartialProm){
  for(int no_parcial=0;no_parcial<4;no_parcial++){
    for(int al=0;al<numAlumnos;al++){
        
            PartialProm[no_parcial]+=UNI[al].P[no_parcial];
        }
    PartialProm[no_parcial]/=numAlumnos;
    }
}


void MAXIMA_CAL(float *PartialProm){
    int cpp=0,saveme2;
    float saveme;
    while(cpp<4){
    saveme =PartialProm[cpp]; 
    saveme2 = cpp-1;
        while (saveme2>=0 && PartialProm[saveme2] > saveme)
        {
            PartialProm[saveme2+1] = PartialProm[saveme2];
            saveme2--;         
            
        }
    PartialProm[saveme2+1] = saveme;
    cpp++;
    }
    printf("\n\n");
  for(cpp=0;cpp<4;cpp++){
        if(PartialProm[3]/PartialProm[cpp]==1){
            printf("\nEl maisimo examen es %.2f",PartialProm[3]);
        }
    }
}