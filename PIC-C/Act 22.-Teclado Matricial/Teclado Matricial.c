//----------- MAIN LIBRARY ----------
      #INCLUDE <18f4550.h> 
//------- FUSES CONFIGURATION -------
#fuses NOWDT,HS,PUT,NOPROTECT,NOBROWNOUT,NOMCLR,NOLVP,NOCPD
#use delay(clock=4000000)
//---------- EXT LIBRARIES -----------
#include <lib kbd.c>
#include <lcd.c>
//----------- SET OUTPUTS -----------
//--Ports-

//--Var--



//--Inicio--
void main(){
      lcd_init();
      kbd_init();
      port_b_pullups(true);
      char O;
      lcd_gotoxy(2,1);
      printf(lcd_putc,"ola");
        
      while(true)
    {
      O=kbd_getc();
      if(O!=0)
      {
      lcd_gotoxy(1,2);
      lcd_putc('\f');
      lcd_putc(O);
      }
    }//End While  

}//End main 



