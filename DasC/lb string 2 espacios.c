/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ printf,Scanf, gets, getch,getche, puts, ----
------------ 31/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
#include <conio.h> //CONsole INput
#include <string.h> //String
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---

char Var_wa[] = "Wa";
int lon_cad;
int main()
{
    char cad[100];
    printf("Ingresa la cadena. \n");
    gets(cad);
    strcat(cad," ");
    lon_cad = strlen(cad);
    cad = strstr(cad," ");
    
    // //strcpy(dest,orig); both arguments must be string type
    // //--STRing CoPY--
    // strcpy(fri,cad);
    // strcpy(fri2,"pene");
    // printf("Stringcopi1 \n %s\n %s\n\n",fri,fri2);
    // //--STRing Number CoPY--
    // fflush(stdin);
    // strncpy(fri,cad,4);
    //     printf("Stringcopinomber \n %s\n\n",fri);
    // //--Concatenate--
    // strcat(Var_wa,cad);
    //     printf("concaneto \n %s\n\n",Var_wa);
    // //--UnConcatenate--
    // cad = strstr(fri,"nos");
    //     printf("noconcaneto \n %s\n\n",cad);    
    // aux = strcmp("pene","pene"); //Compara la longitud de cadena si 1 cad1>cad2,0 cad1=cad2,-1 cad1<cad2
    // int len1 =strlen("pene");
    // int len2 =strlen("pene");
    //     printf("checale \n %d por %d posciones\n\n",aux,len1-len2);

    return 0;

}
