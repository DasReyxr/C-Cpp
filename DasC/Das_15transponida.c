/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ printf,Scanf, gets, getch,getche, puts, ----
------------ 31/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output

//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---

int ii;
int ij;
int xlenght,ylenght, tot;
int main()
{
    printf("Ingresa la cantidad de columnas que deseas tener en tu matriz\n");
    scanf("%d",&xlenght);
    printf("Ingresa la cantidad de filas que deseas tener en tu matriz\n");
    scanf("%d",&ylenght);
    
    int Mat[ylenght][xlenght], Mat2[xlenght][ylenght];
    
    //Save and Print
    for(ii=0;ii<ylenght;ii++){

        for(ij=0;ij<xlenght;ij++){
            printf("Dame posicion {%d, %d} ",ii+1,ij+1);
            scanf("%d",&Mat[ii][ij]);           
            
        }
    }
    //Print the condition A[I][J]=A[J][I]
    printf("\n");

    for(ii=0;ii<xlenght;ii++){

        for(ij=0;ij<ylenght;ij++){
            Mat2[ii][ij] = Mat[ij][ii];     
            printf("%d ",Mat2[ii][ij]);
        }
        printf("\n");
    }
    
    return 0;
}
