/*
------ Kevin Lara ------
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
void configNVIC(void);

void setClkPLL(void);
void SN_sawtooth(void);
void SN_triangle(void);
void SN_sine(void);
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
uint8_t signal = 1;

#define SAWTOOTHWAVE 0
#define TRIANGLEWAVE 1
#define SINEWAVE 2
// ----------- Main -----------

	
int main(void){
	confRCC(); /*Llamada de la funcion*/
	confGPIO();
    confTIMER();
    confDAC();
    configNVIC();
    setClkPLL();
    while(1){

      
        
}
}
	
void confTIMER(void){
	TIM6->CR1 |= (1 << 0)|(1<<7);
	TIM6->CR2 |= (2 << 4);
	/*8MHz/1000 = 8K (actually is 7999) */
    TIM6->PSC = 1;
    TIM6->ARR = 10;
    TIM6->DIER |= (1<<0);
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


void configNVIC(void){
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	NVIC_SetPriority(TIM6_DAC_IRQn, 1);

}



void confGPIO(void){
    GPIOA->MODER |= (3 << 8);
}

void SN_sawtooth(void){
    uint16_t i = 0;
    uint8_t flag = 0;
    while(1){
    while(TIM6->SR & TIM_SR_UIF){
    DAC->DHR12R1 = (DAC->DHR12R1 & (0xFFFFF000) )| (i<<0);
    i= i+5;
    if(i>=4095) i=0;
    TIM6->SR &= ~TIM_SR_UIF;
		}
		
}}

void SN_triangle(void){
    uint8_t flag = 0;
    uint16_t i = 0;

    while(1){
    while(TIM6->SR & TIM_SR_UIF){
    if(flag==0) i=i+5;
    if(flag==1) i=i-5;

    if(i>=4095) flag = 1;
    if(i == 0 & flag == 1 ) flag =0;
    DAC->DHR12R1 = (DAC->DHR12R1 & (0xFFFFF000) )| (i<<0); 
    TIM6->SR &= ~TIM_SR_UIF;
		}
}
}

void SN_sine(void){
    float seno;
    float i=0;
    int ip;
    while (1) {
    //if(TIM6->CNT != TIM6->ARR){
    i+=0.001;
    seno = ((sin(100*i)*4095) + 4095)/2;
    ip=(int)seno;
    DAC->DHR12R1 = (DAC->DHR12R1 & (0xFFFFF000) )| (ip<<0); 
    if(i > 6.283) 
        i =0;
    
   // }
    
    }

    
    
}

void setClkPLL(void)
{
	RCC->CR |=(1 << 16);
	while(!(RCC->CR & RCC_CR_HSERDY));
	/*Acivamos el prefetch del FLASH y cambiamos la latencia entre lectura de la CPU y la memoria a 2 waitstates*/
	FLASH->ACR |= (1<<8) ;
	FLASH->ACR |= (5<<0);
	/*Cambiamos la velicidad del apb1 ya que no puede trabajar a mas de 45MHZ y la de apb2 que no trabaja a mas 90*/
	RCC->CFGR |= (5<<10);
	RCC->CFGR |= (4<<13);
	RCC->PLLCFGR |=(1 << RCC_PLLCFGR_PLLSRC_Pos);
	RCC->PLLCFGR |= (360 << RCC_PLLCFGR_PLLN_Pos) | 
									(8 << RCC_PLLCFGR_PLLM_Pos) | 
									(0 << RCC_PLLCFGR_PLLP_Pos) ;
	/*LAS VELOCIDADES DEL AHB, EL APB1,APB2 DEBEN MODIFICARSE SI CAMBIO LA FRECUENCIA A LA MAS ALTA*/
	RCC->CR |=(1 << 24);
	RCC->CFGR |= (2 << 0);
	SystemCoreClockUpdate();
}

void TIM6_DAC_IRQHandler(void){
   switch (signal) {
    case SAWTOOTHWAVE:
        SN_sawtooth();
        break;
    case TRIANGLEWAVE:
        SN_triangle();
        break;
    case SINEWAVE:
        SN_sine();
        break;
    }   
}