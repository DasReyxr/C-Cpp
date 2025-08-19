/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ 
Alreves goltiao
------
------------ 18/10/2023 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
#include <conio.h> //CONsole Input
#include <stdbool.h> //STandart Bool
//--- Global Var ---
const int TAM=2;
//-Prototipado

void readnum(int *,int);
bool operacion(int*);
int main()
{
    int nums[TAM];
    bool answer;
    readnum(nums,TAM); //Si no se prototipara tendria que llevar nums[]
    // if(operacion(nums)){
    //     printf("Si");
    // }
    answer= operacion(nums);
    (operacion(nums)) ? printf("es multiplo") : printf("no es multiplo");
    getch();    
    return 0;
}

void readnum(int A[], int size){
    for(int i=0; i<size;i++){
        printf("\nDame dos numeros %d ", i+1);
        scanf("%d",&A[i]);
    }
    printf("cakturados\n");
}
bool operacion(int A[]){
    if(A[0]%A[1]==0){
        return 1;
    }
    else{
        return 0;
    }
}