/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ Switch Lade ----
------------ 08/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
 
//--- Global Var ---
unsigned int time;
unsigned int Zona;
float Price;
int main()
{
    printf("Ingrese el tiempo de la llamada en minutos  \n");
    scanf("%d",&time); 
    printf("Ingrese la zona \n 1) USA 2) Canada \n 5) America de Sur 6) America Central 7) Mexico \n 9) Europa 10) Asia 15) Africa 20) Oceania  \n");
    scanf("%d",&Zona);
    
    switch(Zona){
        case 1: //Estados Unidos
            Price=0.13*time;
            break;
        case 2: //Canada
            Price=0.11*time;
            break;
        case 5: //Sudamerica
            Price=0.22*time;
            break;
        case 6: //America Central
            Price=0.19*time;
            break;
        case 7: //Mexico
            Price=0.17*time;
            break;
        case 9: //Europa
            Price=0.17*time;
            break;
        case 10: //Asia
            Price=0.20*time;
            break;
        case 15: //Africa
            Price=0.39*time;
            break;
        case 20: //Oceania
            Price=0.28*time;
            break;
    }
    printf("El costo es: %f", Price);
}
