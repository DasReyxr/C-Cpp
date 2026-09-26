//----------- MAIN LIBRARY ----------
      #include <18F4550.h> 
//------- FUSES CONFIGURATION -------
#fuses NOWDT,HS,PUT,NOPROTECT,NOBROWNOUT,NOLVP,NOCPD
#use delay(clock=4MHz)

//---------- EXT LIBRARIES -----------
#include <lcd.c>
//----------- SET OUTPUTS -----------
//--Ports-
//--Var--
int8 unit; //define unit as a variable of 8 bits
//--Inicio--

void main(){
      lcd_init();
         while(true)
         {
         while(unit<=9)
            {
         lcd_gotoxy(1,1); //go to position 1,1 columna 1 fila 1
         printf(lcd_putc,"Contador 0-9"); //Print "Contador 0-9"
         lcd_gotoxy(1,2);  //go to position 1,2 xy
         printf(lcd_putc,"Unidades %1u", unit); //1->1 digit (0-9) u->unsigned
         delay_ms(300);
         unit++;
            }//end while condition
         unit=0;
         }//end while
         
   }//end main
  
   
