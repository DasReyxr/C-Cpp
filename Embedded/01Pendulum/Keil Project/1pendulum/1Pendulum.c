/*
------ Orlando Reyes ------
--------- Auf Das ---------
----------- Test -----------
-------- 18/08/2025 --------
*/
// ------- Main Library -------
#include <stm32f446xx.h>

// --------- Function ---------
void confRCC(void);
void confGPIO(void);
void delay_ms(uint32_t delay);
// ---------- Class ----------
uint16_t veclit [18] = {0x3800,0x1C00,0x0E00,0x0700,0x0300,0x0100,0x0300,0x0700,0x0E00,0x1C00,0x3800,0x7000,0xE000,0xC000,0x8000,0xC000,0xE000
}; 
// -------- Variables --------
// ----------- Main -----------

int main(void){
	confRCC(); 
	confGPIO();
	uint8_t delay_val = 50;

	while(1){
	for(uint8_t i = 0;i<17;i++){
	GPIOE->ODR = veclit[i]; // Set the output data register
	delay_ms(delay_val);
	if(GPIOA->IDR  & (1 << 5) & delay_val < 100) 
	{
	delay_val = delay_val + 1;	
	}
	if(GPIOA->IDR  & (1 << 6) & delay_val >0) 
	{
	delay_val = delay_val - 1;	
	}
	


	}

	}}
/*
	if(GPIOA->IDR & (1<<0)){}
	lecPA0 = (uint8_t)GPIOA-IDR;
	if(lecPA= & (1<<0))
*/
	 
	


void confRCC(void){
	/*Encendemos el clk en Pc,PE,PF*/
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 
	
}



void confGPIO(void){
	
	GPIOE->MODER |= (0x5555 << 16); // PE8 -> PE15 Output 


	GPIOA->PUPDR |= (0xA << 10); //PA5 y PA6 como entrada PA5  + PA6 -
}
// 3 bits en 8 
// Input PA5 PA6


void delay_ms(uint32_t delay){
	for(uint32_t i=0;i<delay;i++){
	for(uint32_t j=0;j<11500;j++);

	}

}
