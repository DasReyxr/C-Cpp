/*
------ Orlando Reyes ------
--------- Auf Das ---------
----------- Test -----------
-------- 09/09/2025 --------
LED1 PA5 
LED2 PA6
Button PE8
*/

// ------- Main Library -------
#include <stm32f446xx.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/*Parámetros*/
#define initialms 100U
#define finalms 1000U
// --------- Function ---------
void confRCC(void);
void confGPIO(void);
/*FREE RTOS FUNCTION*/
void vTaskLedButton (void *);
void vTaskLedFreq   (void *);
void vTaskButton    (void *);


QueueHandle_t xPeriodQueue = NULL;

/**/
// ---------- Class ----------
 
// -------- Variables --------
// ----------- Main -----------

int main(void){
	confRCC(); 
	confGPIO();
	
	xPeriodQueue = xQueueCreate(2,sizeof(uint32_t));
	xTaskCreate(vTaskButton,"LED TASK2",100,NULL,1,NULL);
    xTaskCreate(vTaskLedButton,"LED TASKk",100,NULL,2,NULL);
    xTaskCreate(vTaskLedFreq,"LED TASK",100,NULL,2,NULL);

    vTaskStartScheduler();
	while(1);
}

void confRCC(void){
	RCC->AHB1ENR |= (1 << 0) | (1 << 4); // A  E 	
}



void confGPIO(void){
	
	GPIOA->MODER |= (5 << 10); // PA5 Y PA6 Output 
	GPIOE->PUPDR |= (1 << 16);// PE8 Button
}
// 3 bits en 8 
// Input en PUERTO E
void vTaskLedButton (void *pvPARAMETERS){
	
	uint32_t recievedQueue;
	while(1){ 
		TickType_t waitsTicks = (pdMS_TO_TICKS (10));
		if(xQueueReceive(xPeriodQueue,&recievedQueue,waitsTicks) == pdPASS)/*Recibimos el estado de la tarea2 del botoón cuando se presiono el botón si llega al tope */
		{
			if (recievedQueue == 0){
	    GPIOA->ODR ^= (1 << 5);}
		}
    }
   
}



void vTaskLedFreq (void *pvPARAMETERS){
    uint16_t vec[2] = {500,250};
    uint8_t pos =0;

	uint32_t recievedQueue;
	while(1){ 
		TickType_t waitsTicks = (pdMS_TO_TICKS (vec[pos]));
		if(xQueueReceive(xPeriodQueue,&recievedQueue,waitsTicks) == pdPASS)/*Recibimos el estado de la tarea2 del botoón cuando se presiono el botón si llega al tope */
		{
			if(recievedQueue == 0){
			pos ^= 1;}
         }
		 GPIOA->ODR ^= (1 << 6);
	}
}
	

void vTaskButton(void *pvPARAMETERS){
    uint32_t lastState = 1;/*comprueba el ultimo estado del botón*/
	while(1){
		uint32_t actualState;
		if(!((GPIOE->IDR) & (1 << 8)))
			actualState = 0;
			else 
				actualState = 1;
			if(lastState ==1 && actualState == 0 )
			{
				vTaskDelay(pdMS_TO_TICKS(20));
				xQueueSend(xPeriodQueue,&actualState,pdMS_TO_TICKS(20));
				xQueueSend(xPeriodQueue,&actualState,pdMS_TO_TICKS(20));
			}
			lastState= actualState;
	vTaskDelay(pdMS_TO_TICKS(50));
	}
}