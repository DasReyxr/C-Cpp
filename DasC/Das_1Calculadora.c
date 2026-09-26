/*-------- Orlando Contreras -------
------------- Reyes Das -------------
------ printf,Scanf, gets, getch,getche, puts, ----
------------ 31/08/2022 ------------*/
//----------- MAIN LIBRARY ----------
#include <stdio.h> //Standart Data Input-Output
#include <conio.h> //CONsole INput
#include <stdlib.h> //Standart Library
//---------- EXT LIBRARIES -----------
//----------- SET OUTPUTS ----------- 
//--- Global Var ---
int a,b,c;
int sum, delta,prod;
int opt;
int opt2;
char name[10];
int main()
{
            
    //--- Subrutine juan ---
    juan: 
        printf("Input ur name \n");
        gets(name);
        printf("Enter the variables \n");                                                   //printf
        scanf("%d %d %d",&a,&b,&c);                                                          //Scanf


        printf("The variables are [%d,%d,%d]",a,b,c);
        printf("\nWould you like to proceed?\nYes) 1 No) 0 Exit) Any key\n");
        opt = getch();                                                           //Getch
        putchar(opt);                                                            //putchar

    if(opt == 0x31)
        {
            sum = a+b+c;
            delta = a-b-c;
            prod = a*b*c;
            printf("\nhi %s there are ur results: ",name);
            printf("\nThe sum     of %d + %d + %d = %d",a,b,c,sum);
            printf("\nThe delta   of %d - %d - %d = %d",a,b,c,delta);
            printf("\nThe product of %d * %d * %d = %d",a,b,c,prod);

            printf("\n\n\nWould you like to do it again?\nYes) 1 No) 0 Exit) Any key\n");
            opt2 = getche();                                                                //getche1
            if ( opt2 == 49)
                {
                    system("cls");
                    puts("avrotrabes \n");                                      //puts
                    goto juan;
                }    
        }
    else if (opt == 0x30)
        {
            system("cls");
            
            printf("avrotrabes \n");
            goto juan;
        }
    return 0;

}
