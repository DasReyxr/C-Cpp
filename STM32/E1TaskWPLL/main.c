/*
------ Orlando Reyes ------
--------- Auf Das ---------
----------- Test -----------
-------- 18/08/2025 --------
*/
// ------- Main Library -------
#include <stm32f446xx.h>
#include <FreeRTOS.h>
#include <task.h>
// --------- Function ---------
void confRCC(void);
void confGPIO(void);
// --------- Function ---------
void vTaskLed300(void *);
void vTaskLed700(void *);

// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

	
int main(void){
	confRCC(); 
	confGPIO();
    /*Create Tasks*/
    xTaskCreate(vTaskLed300, "LED Task", 100, NULL, 1, NULL);
    xTaskCreate(vTaskLed700, "LED Task2", 100, NULL, 2, NULL);
    /*Created*/
    vTaskStartScheduler();
    while(1);

}
/* Implementacion */	 

void vTaskLed300(void *pvParameters){
    while(1){
	GPIOA->ODR ^= ( 1 << 6); /* Encendemos el Led del puerto A6*/
    vTaskDelay(300/portTICK_PERIOD_MS); 
    }
}


void vTaskLed700(void *pvParameters){
    while(1){
	GPIOA->ODR ^= ( 1 << 5); /* Encendemos el Led del puerto A5*/ 
    vTaskDelay(700/portTICK_PERIOD_MS); 
    }
}




void confRCC(void){
	RCC->AHB1ENR |= (1 << 0);
}



void confGPIO(void){
  	GPIOA->MODER |= (5 <<10); /*A5 y A6 */
}


void setClkPLL(void)
{
    /*para 82 MHz*/
	RCC->CR |=(1 << 16);
	while(!(RCC->CR & RCC_CR_HSERDY));
	/*Acivamos el prefetch del FLASH y cambiamos la latencia entre lectura de la CPU y la memoria a 2 waitstates*/
	FLASH->ACR |= (1<<8) ;
	FLASH->ACR |= (2<<0); /*2 wait states pq ta entre 60 y 90*/
	/*Cambiamos la velicidad del apb1 ya que no puede trabajar a mas de 45MHZ y la de apb2 que no trabaja a mas 90*/
	RCC->CFGR |= (4<<10); /*APb1 2 prescaler*/
	/*RCC->CFGR |= (4<<13);*/
	/* Seleccionamos PLLSRC RCC->PLLCFGR |=(1 << RCC_PLLCFGR_PLLSRC_Pos);*/
	RCC->PLLCFGR |= (82 << RCC_PLLCFGR_PLLN_Pos) | 
                    (4 << RCC_PLLCFGR_PLLM_Pos) | 
                    (1 << RCC_PLLCFGR_PLLP_Pos) ;
	/*LAS VELOCIDADES DEL AHB, EL APB1,APB2 DEBEN MODIFICARSE SI CAMBIO LA FRECUENCIA A LA MAS ALTA*/
	RCC->CR |=(1 << 24);
	RCC->CFGR |= (2 << 0);
	SystemCoreClockUpdate();
}

