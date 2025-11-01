/*
------ Orlando Reyes ------
--------- Auf Das ---------
------- Semaphores ---------
-------- 09/22/2025 --------
We would generate two task that would be handle by a semaphore
The first task would blink 5 times after  led the second task annd
would blink 10 times
*/
// ------- Main Library -------
#include <stm32f446xx.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
// --------- Function ---------
//=-------- Parametros ---------
#define initialMs 100U
#define finalMs 2000U

void confRCC(void);
void confGPIO(void);
// --------- Function ---------
// ---- Administradores ----
QueueHandle_t xPeriodQueue = NULL;
SemaphoreHandle_t SemaphoreA = NULL;
SemaphoreHandle_t SemaphoreB = NULL;

void vtaskA(void *);
void vtaskB(void *);

void vTaskLed(void *);
void vTaskButton(void *);

// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

	
int main(void){
	confRCC(); /*Llamada de la funcion*/
	confGPIO();


    /*Create Tasks*/
    xPeriodQueue= xQueueCreate( 1, sizeof( uint32_t ) );
    SemaphoreA = xSemaphoreCreateBinary();
    SemaphoreB = xSemaphoreCreateBinary();

    xSemaphoreGive(SemaphoreB);
    xTaskCreate(vtaskA, "Task A", 100, NULL, tskIDLE_PRIORITY+1, NULL);
    xTaskCreate(vtaskB, "Task B", 100, NULL, 1, NULL);
    xTaskCreate(vTaskLed, "LED Task", 100, NULL, 1, NULL);
    /*Created*/
    vTaskStartScheduler();

    while(1);

}
/* Implementacion */	 
void vtaskA(void *pvParameters){
    (void)  pvParameters;
    uint32_t period = initialMs;

    while(1){
    xSemaphoreTake(SemaphoreA, portMAX_DELAY);
    for(uint8_t i=0; i<10; i++){
        GPIOA->ODR ^= ( 1 << 5);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    }
    period += initialMs; 
    xSemaphoreGive(SemaphoreB);

    if(xQueueSend(xPeriodQueue, &period, portMAX_DELAY) != pdPASS){
    uint32_t temp;
    if(xQueueReceive(xPeriodQueue, &temp, 0) == pdPASS){
        (void) xQueueSend(xPeriodQueue, &period, portMAX_DELAY);
    }
}

}

void vtaskB(void *pvParameters){
    (void) pvParameters;
    while(1){
    xSemaphoreTake(SemaphoreB, portMAX_DELAY);
    for(uint8_t i=0; i<20; i++){
        GPIOA->ODR ^= ( 1 << 6);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
    }
    xSemaphoreGive(SemaphoreA);
}


void vTaskLed(void *pvParameters){
    (void) pvParameters;
    uint32_t initDelay     = initialMs;
    uint32_t receivedQueue;
    while(1){
	GPIOA->ODR ^= ( 1 << 7);
    vTaskDelay(initDelay/portTICK_PERIOD_MS); 
    //BaseType_t 
    TickType_t waitTicks= pdMS_TO_TICKS(initDelay);     
    /*Va revisar lo que hay en la cola de xperiodqueue cada inicialms*/
    if(xQueueReceive(xPeriodQueue, &receivedQueue, portMAX_DELAY) == pdPASS){ /*Es el & pa que envie el inicio del struct */
        if(receivedQueue < 1)
         receivedQueue = initialMs;            
    if(receivedQueue >= finalMs)
            receivedQueue = finalMs;                
    initDelay = receivedQueue;            
    }
}}




void confRCC(void){
	/*Encendemos el clk en PA*/
	RCC->AHB1ENR |= (1 << 0);
	
}



void confGPIO(void){

  	GPIOA->MODER |= (0x15 <<10); /*A5 y A6 A7*/
    GPIOA->OSPEEDR |= (0x3F <<10); /*A5 y A6 A7*/
    
	
	
}

