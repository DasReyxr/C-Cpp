/*
--------- Auf Das  ---------
----------- LCD  -----------
-------- 02/10/2025 --------
*/
// ------- Main Library -------
#include "conf.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

// --------- Function ---------
void confRCC(void);
void confGPIO(void);
void delay_ms(uint32_t delay);

void vTaskLed (void *);
void vTaskLCD (void *);

// ---------- Class ----------
// -------- Variables --------
uint16_t Count = 0;
// ----------- Main -----------

int main(void){
	config();
	LCD_Init4B();
 
    xTaskCreate(vTaskLCD,"LED LCD",100,NULL,1,NULL);
    xTaskCreate(vTaskLed,"LED LED",100,NULL,2,NULL);

    vTaskStartScheduler();

	while(1);
}
void vTaskLed(void *pvParameters){
    while(1){
	GPIOA->ODR ^= ( 1 << 0);
    vTaskDelay(500/portTICK_PERIOD_MS); 
	GPIOA->ODR ^= ( 1 << 0);
    vTaskDelay(500/portTICK_PERIOD_MS); 
    }
}


void EXTI0_IRQHandler(void){
    if(EXTI->PR & (1<<0)){ // Verificamos que la interrupcion provenga de la linea 0
    Count++;
EXTI->PR |= (1<<0); // Limpiamos la bandera de la interrupcion< 
    }

}


void vTaskLCD (void *pvParameters){
    while(1){
    while (TIM3->SR & TIM_SR_UIF)
	{
        LCD_Clear();

        LCD_WriteINT(Count);
        Count = 0;

        TIM3->SR &= ~TIM_SR_UIF;	
	}

    }
}


