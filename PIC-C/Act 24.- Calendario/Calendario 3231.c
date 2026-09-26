//----------- MAIN LIBRARY ----------
#include <18F452.h> 
//-------- ADC CONFIGURATION --------
//------- FUSES CONFIGURATION -------
#fuses NOWDT,HS,PUT,NOPROTECT,NOBROWNOUT,NOLVP,NOCPD
#use delay(clock=4MHz)
//---------- EXT LIBRARIES -----------
#include <lcd.c>
#include <DS3231.c>
//----------- SET OUTPUTS -----------
//--Ports-
//--Var--


//--Inicio--
void main(){
         //Set Outputs
         lcd_init();//initialize the lcd and rtc
         rtc_begin();
         rtc.setDOW(LUN);     // Set Day-of-Week to SUNDAY
         rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
         rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
         
   
         //Infinite Loop
         while(true){
         Serial.print(rtc.getDOWStr());
         Serial.print(" ");
  
        // Send date
        Serial.print(rtc.getDateStr());
        Serial.print(" -- ");
        // Send time
        Serial.println(rtc.getTimeStr());
         
         ds1307_get_date(d,m,yr,dow);
         ds1307_get_time(h,min,s);
         ds1307_get_day_of_week(fecha);
         
         lcd_gotoxy(1,1);//row 1
            printf(lcd_putc,"%s %02u/%02u/20%02u",fecha,d,m,yr);
         lcd_gotoxy(1,2);//row 2
            printf(lcd_putc,"%02u:%02u:%02u",h,min,s);
         delay_ms(100);
         
         }//end while
         
}//end main
  
   
