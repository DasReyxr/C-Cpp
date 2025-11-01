//----------- MAIN LIBRARY ----------
      #include <18F452.h> 
//------- FUSES CONFIGURATION -------
#fuses NOWDT,HS,PUT,NOPROTECT,NOBROWNOUT,NOLVP,NOCPD
#use delay(clock=4MHz)

//---------- EXT LIBRARIES -----------
#include <lcd.c>
#define use_portb_kbd TRUE
#include <4kbd4.c>
//----------- SET OUTPUTS -----------
//--Ports-
//--Var--
char o;
//--Inicio--

void main(){
         lcd_init();//initialize the lcd and the keyboard
         kbd_init();
         port_b_pullups(true);
         
         while(true){
         o=kbd_getc();//save the value of keyboard on "o"
         if (o !=0){
            lcd_gotoxy(1,2);//print the 'o' on lcd
            lcd_putc(o);
         }
         }//end while
         
}//end main
  
   
