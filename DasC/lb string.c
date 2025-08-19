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
char *oal = "Hola alumnosssssssss ";
char Var_wa[] = "Wa";
char fri[20],fri2[20],fri3[];
int aux;
int main()
{
    //strcpy(dest,orig); both arguments must be string type
    //--STRing CoPY--
    strcpy(fri,oal);
    strcpy(fri2,"pene");
    printf("Stringcopi1 \n %s\n %s\n\n",fri,fri2);
    //--STRing Number CoPY--
    fflush(stdin);
    strncpy(fri,oal,4);
        printf("Stringcopinomber \n %s\n\n",fri);
    //--Concatenate--
    strcat(Var_wa,oal);
        printf("concaneto \n %s\n\n",Var_wa);
    //--UnConcatenate--
    oal = strstr(fri,"nos");
        printf("noconcaneto \n %s\n\n",oal);    
    aux = strcmp("pene","pene"); //Compara la longitud de cadena si 1 cad1>cad2,0 cad1=cad2,-1 cad1<cad2
    int len1 =strlen("pene");
    int len2 =strlen("pene");
        printf("checale \n %d por %d posciones\n\n",aux,len1-len2);
    return 0;

}
