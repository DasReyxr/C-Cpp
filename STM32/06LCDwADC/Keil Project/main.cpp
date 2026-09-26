/*
------- Kevin Lara  -------
--------- Auf Das  ---------
----------- LCD  -----------
-------- 02/10/2025 --------
*/
// ------- Main Library -------
#include "conf.h"

// --------- Function ---------
void confRCC(void);
void confGPIO(void);
void delay_ms(uint32_t delay);
// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

int main(void){
	config();
	LCD_Init4B();

    LCD_WriteINT(127);
	uint16_t lastCont = TIM4->CNT;

	while(1){
		lastCont = contPulses(lastCont);
    while (TIM3->SR & TIM_SR_UIF)
	{
        /*lastCont*60/10 = lastCont*6/1*/
		uint16_t RPM = lastCont*6;
    
			LCD_Clear();

        LCD_WriteINT(RPM);
        LCD_WriteString(" RPM");
		
        lastCont = 0;
        TIM3->SR &= ~TIM_SR_UIF;	
	}
    }
}
	 
	

