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
int numAlumnos;
int id;
int pos_parcial,pos_id; //X,y
char tring[100];
int iterative;
int cal,num,letra;
int lenghtof;   
int numParciales;
//int Cal_Alumnos[4][];    
int main()
{
    printf("Repetidor de litras Auf Das \n");
    printf("Ingresa numero parciales");
    //scanf("%d",&numParciales);
    numParciales=4;
    printf("Ingresa numero de alumnos\n");
    scanf("%d",&numAlumnos);
    int names[numAlumnos][numParciales+1];
    

    for(jterative=0;jterative<numAlumnos;jterative++){
        printf("Ingrese nombre ID Alumno\n");
        scanf("%d",&id);
        names[jterative]=id;        
        printf("ID Alumno: %d\n", names[jterative]);
    }
    
    for(int y=0;y>numAlumnos;y++){
        for(int x=1;x>=numParciales;x++){
        printf("Ingrese calificacion de %d de parcial %d",pos_id,pos_parcial);
        scanf(&cal);
        names[x][y]=cal;
        printf("%d",names[x][y])
        }
    }
    

    // for(jterative=0;jterative<numAlumnos;jterative++)
    // {    
    //     for(iterative=0;iterative<5;iterative++){
    //         printf("Ingresa calificacion %d de alumno %d \n",iterative+1,jterative+1);
    //         scanf(&cal);
    //         Cal_Alumnos[jterative][iterative]=cal;
    //     }
    // }
    


 
    

    return 0;
}
