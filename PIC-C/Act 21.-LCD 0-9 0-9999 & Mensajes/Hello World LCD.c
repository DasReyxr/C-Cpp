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
//--Inicio--

void main(){
      lcd_init();
      
         while(true)
         {
         lcd_gotoxy(1,1);
         printf(lcd_putc,"Hola Orlando");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"Fuga por unostacos");
         }//end while
         
   }//end main
  
   
