//----------- MAIN LIBRARY ----------
#include <18F452.h> 
//-------- ADC CONFIGURATION --------
#device adc=10
//------- FUSES CONFIGURATION -------
#fuses NOWDT,HS,PUT,NOPROTECT,NOBROWNOUT,NOLVP,NOCPD
#use delay(clock=4MHz)
//---------- EXT LIBRARIES -----------
#include <lcd420.c>

//----------- SET OUTPUTS -----------
//--Ports-
//--Var--
int16 array[7];
float array2[7];
int16 adc;
float analog;
//--Inicio--

void main(){
         //Set Outputs
         setup_adc_ports(ALL_ANALOG);//Set the ports
         setup_adc(ADC_CLOCK_INTERNAL);//Set the speed of clock
         lcd_init();//initialize the lcd
         
         //Infinite Loop
         while(true){ 
         
         for(adc=0,analog=0;adc<7;adc++,analog++){
            set_adc_channel(adc);
            delay_us(20);
            array[adc]=read_adc();  
            array2[analog]=5.0*array[adc]/1024.0;
         }      
         
         lcd_gotoxy(1,1);
            printf(lcd_putc,"1=%01.2fV",array2[0]);
         lcd_gotoxy(10,1);
            printf(lcd_putc,"2=%01.2fV",array2[1]);            
         lcd_gotoxy(1,2);
            printf(lcd_putc,"3=%01.2fV",array2[2]);
         lcd_gotoxy(10,2);
            printf(lcd_putc,"4=%01.2fV",array2[3]);
         lcd_gotoxy(17,1);
            printf(lcd_putc,"5=%01.2fV",array2[4]);
         lcd_gotoxy(26,1);
            printf(lcd_putc,"6=%01.2fV",array2[5]);
         lcd_gotoxy(17,2);
            printf(lcd_putc,"7=%01.2fV",array2[6]);
         lcd_gotoxy(26,2);
            printf(lcd_putc,"8=%01.2fV",array2[7]);                                 
         }//end while
         
}//end main
