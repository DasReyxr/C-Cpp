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
int16 adc1,adc2,adc3,adc4,adc5,adc6,adc7,adc8;
//--Inicio--

void main(){
         //Set Outputs
         setup_adc_ports(ALL_ANALOG);//
         setup_adc(ADC_CLOCK_INTERNAL);//Set the speed of clock
         lcd_init();//initialize the lcd
         
         //Infinite Loop
         while(true){ 
         
         set_adc_channel(0); //Enable Channel 0
            delay_us(20);
         adc1=read_adc();//save the value of adc on "adc1"
         set_adc_channel(1); //Enable Channel 0
            delay_us(20);         
         adc2=read_adc();//save the value of adc on "adc2"
         set_adc_channel(2); //Enable Channel 0
            delay_us(20);
         adc3=read_adc();//save the value of adc on "adc3"
         set_adc_channel(3); //Enable Channel 0
            delay_us(20);
         adc4=read_adc();//save the value of adc on "adc4"
         set_adc_channel(4); //Enable Channel 0
            delay_us(20);
         adc5=read_adc();//save the value of adc on "adc5"
         set_adc_channel(5); //Enable Channel 0
            delay_us(20);
         adc6=read_adc();//save the value of adc on "adc6"
         
         lcd_gotoxy(1,1);
            printf(lcd_putc,"ADC=%4ld",adc1);
         lcd_gotoxy(10,1);
            printf(lcd_putc,"ADC=%4ld",adc2);            
         lcd_gotoxy(2,1);
            printf(lcd_putc,"ADC=%4ld",adc3);
         lcd_gotoxy(2,10);
            printf(lcd_putc,"ADC=%4ld",adc4);
         lcd_gotoxy(17,1);
            printf(lcd_putc,"ADC=%4ld",adc5);
         lcd_gotoxy(27,1);
            printf(lcd_putc,"ADC=%4ld",adc6);
         lcd_gotoxy(17,2);
            printf(lcd_putc,"ADC=%4ld",adc7);
         lcd_gotoxy(27,2);
            printf(lcd_putc,"ADC=%4ld",adc8);                                 
         }//end while
         
}//end main
  
   
