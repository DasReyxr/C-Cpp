//----------- MAIN LIBRARY ----------
      #INCLUDE <18f4550.h> 
//------- FUSES CONFIGURATION -------
//#fuses XTPLL,MCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL1,CPUDIV1,NOVREGEN
#fuses NOWDT,HS,PUT,NOPROTECT,NOBROWNOUT,NOMCLR,NOLVP,NOCPD
#use delay(clock=4000000)

//---------- EXT LIBRARIE -----------
#include <lcd.c>

//----------- SET OUTPUTS -----------
//--Ports-
#byte Port_D = 0X0F83 // Port_D es equivalente a la dirección de RAM 0F83
#byte Tris_D = 0x0F95 // Tris_D es equivalente a la dirección de RAM 0F95
//--Var--


//--Inicio--
void main(){
   Tris_D = 0x00;//  Set TRISD as OUTPUT
   Port_D = 0X00; // Leds OFF 
   
   while(true){            
   bit_set (Port_D,7); // Prende la Vuelta del SEM_1
   bit_set (Port_D,4); // Prende el Rojo del SEM_1
   bit_set (Port_D,0); // Prende el Rojo del SEM_2
      delay_ms(1000); // Se llama subrutina delay en milisegundos, entonces pasa un segundo

   bit_clear (Port_D,7); // Se apaga la Vuelta del SEM_1
   bit_clear (Port_D,4); // Se apaga el Rojo del SEM_1
   bit_set (Port_D,6); // Prende la Verde del SEM_1
      delay_ms(1000); // Se llama subrutina delay en milisegundos, entonces pasa un segundo

   bit_clear (Port_D,6); // Se apaga el Verde del SEM_1
   bit_set (Port_D,5); // Prende la Amarillo del SEM_1
      delay_ms(1000); // Se llama subrutina delay en milisegundos, entonces pasa un segundo

   bit_clear (Port_D,5); // Se apaga el Amarillo del SEM_1
   bit_set (Port_D,4); // Prende la Rojo del SEM_1
   bit_set (Port_D,3); // Prende la Vuelta del SEM_2
      delay_ms(1000); // Se llama subrutina delay en milisegundos, entonces pasa un segundo

   bit_clear (Port_D,3); // Se apaga la Vuelta del SEM_1
   bit_clear (Port_D,0); // Se apaga el Rojo del SEM_1
   bit_set (Port_D,2); // Prende la Verde del SEM_1
      delay_ms(1000); // Se llama subrutina delay en milisegundos, entonces pasa un segundo

   bit_clear (Port_D,2); // Se apaga el Verde del SEM_1
   bit_set (Port_D,1); // Prende la Amarillo del SEM_1
      delay_ms(1000); // Se llama subrutina delay en milisegundos, entonces pasa un segundo

   }
}



