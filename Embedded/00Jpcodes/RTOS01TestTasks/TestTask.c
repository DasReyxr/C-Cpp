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
void vTaskLed(void *);
void vTaskButton(void *);

// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

	
int main(void){
	confRCC(); /*Llamada de la funcion*/
	confGPIO();

    /*
xTaskCreate( TaskFunction_t pxTaskCode, const char * const pcName, 
const configSTACK_DEPTH_TYPE uxStackDepth, void * const pvParameters,
UBaseType_t uxPriority, TaskHandle_t * const pxCreatedTask ) PRIVILEGED_FUNCTION;
*/
    /*Create Tasks*/
    xTaskCreate(vTaskLed, "LED Task", 100, NULL, 1, NULL);
    xTaskCreate(vTaskButton, "BUTTON Task", 100, NULL, 2, NULL);
    /*Created*/
    vTaskStartScheduler();

    while(1);

}
/* Implementacion */	 

void vTaskLed(void *pvParameters){
    while(1){
	GPIOA->ODR ^= ( 1 << 6);
    vTaskDelay(500/portTICK_PERIOD_MS); /*1/2 segundo*/

    }
}
void vTaskButton(void *pvParameters){
    for(;;){
        if(!(GPIOA->IDR & (1 << 8)))
            GPIOA->ODR ^= (1 << 5);
    vTaskDelay(100/portTICK_PERIOD_MS); /*1/2 segundo*/

    
    }
}


void confRCC(void){
	/*Encendemos el clk en PA*/
	RCC->AHB1ENR |= (1 << 0);
	
}



void confGPIO(void){
  	GPIOA->MODER |= (5 <<10); /*A5 y A6 */
    GPIOE->PUPDR |= (0x1 <<16); /*Pull up in A8 */
    /*Button 8*/
	
	
}

