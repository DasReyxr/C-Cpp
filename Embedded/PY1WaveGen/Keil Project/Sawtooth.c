/*
------ Orlando Reyes ------
--------- Auf Das ---------
----------- Test -----------
-------- 18/08/2025 --------
*/
// ------- Main Library -------
#include <stm32f446xx.h>
#include <math.h>


// --------- Function ---------
void confTIMER(void);
void confDAC(void);
void confRCC(void);
void confGPIO(void);
// ---------- Class ----------
/*
TIMER
      CR1[ 0 ]= CEN =  1 
      CR2[6-4]= MMS =  2
 DAC
       CR[5-3]= SEL   =  0 (for Timer 6)
       CR[2]  = TEN1  =  1
       CR[1]  = BOFF1 =0
       CR[0]  = EN    = 1
       DHR12R1 <= Datos [12:0]
       DOR => PA4
 RCC
     APB1ENR [29] = DAC    = 1
             [4]  = T6     = 1 
     AHB1ENR [0]  = PortA  = 1
GPIOA 
    MODER [8-9]  = 1  (PA4 Analog)

*/
// -------- Variables --------
// ----------- Main -----------

	
int main(void){
	confRCC(); /*Llamada de la funcion*/
	confGPIO();
    confTIMER();
    confDAC();
    uint16_t i = 0;
    while(1){        
        if(TIM6->CNT == 1000){
        i= i+5;   
        }
        if(i>=4095) i=0;
        DAC->DHR12R1 = (DAC->DHR12R1 & (0xFFFFF000) )| (i<<0); 

        }
}
	
void confTIMER(void){
	TIM6->CR1 |= (1 << 0);
	TIM6->CR2 |= (2 << 4);
	/*8MHz/1000 = 8K (actually is 7999) */
    TIM6->PSC = 1000;
    TIM6->ARR = 1000;
    /*ARR is the frequency of the output*/
}
void confDAC(void)
{
	DAC->CR |= (0 << 3) | (1 << 2) | (1 << 0);
}

void confRCC(void){
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB1ENR |= (1 << 29) | (1 << 4);
}



void confGPIO(void){
    GPIOA->MODER |= (3 << 8);
	
	
}