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
  char CARRERA[20];
  float PROMEDIO;
  char DIRECCION[50];
};    

int main()
{
    struct ALUMNO a1={"Orlando",348390,"Electronica",8.5,"Aguascalientes"},a2,a3;
    //struct *a4;
    char alumno[50],carrera[25],direccion[50];
    int id;
    float promedio;

    printf("gusmornin Auf Das \n");
    printf("Ingresa nombre alumno\n");
        gets(a2.ALUMNO);
    printf("Ingresa matricula alumno\n");
        scanf("%d",&a2.ID);
    printf("Ingresa carrera alumno\n");
        gets(a2.CARRERA);
    printf("Ingresa Promedio alumno\n");
        scanf("%f",&a2.PROMEDIO);
    printf("Ingresa direccion alumno\n");
        gets(a2.DIRECCION);
    //Podemos guardarlo en variables locales del main, solo que para strings usariamos strcopy(receptor,emisor)

    //Printing Section
    puts("----- Alumno 1 -----");
    printf("\tID: %d\n\tNombre %s\n\tCarrera %s\n\tPromedio %.2f\n\tDireccion %s",a2.ID,a2.ALUMNO,a2.CARRERA,a2.PROMEDIO,a2.DIRECCION);
    

    return 0;
}
