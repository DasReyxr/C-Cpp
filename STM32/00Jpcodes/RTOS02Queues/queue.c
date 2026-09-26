/*
------ Orlando Reyes ------
--------- Auf Das ---------
----------- Test -----------
-------- 09/09/2025 --------
We will generate two task, one that will blink at a 100 ms, and the other one
would increment the frequency
*/

// ------- Main Library -------
#include <stm32f446xx.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
// --------- Function ---------
//=-------- Parametros ---------
#define initialMs 100U`
#define finalMs 1000U

void confRCC(void);
void confGPIO(void);
// --------- Function ---------
/*
typedef enum {
    CMD_BLINK = 0,
    CMD_ON = 1,
    CMD_OFF = 2 
    } ledCMD_t;
*/
QueueHandle_t xPeriodQueue = NULL;

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
    xPeriodQueue= xQueueCreate( 1, sizeof( uint32_t ) );

    xTaskCreate(vTaskLed, "LED Task", 100, NULL, 1, NULL);
    xTaskCreate(vTaskButton, "BUTTON Task", 100, NULL, 2, NULL);
    /*Created*/
    vTaskStartScheduler();

    while(1);

}
/* Implementacion */	 

void vTaskLed(void *pvParameters){
    (void) pvParameters;
    uint32_t initDelay     = initialMs;
    uint32_t receivedQueue;
    while(1){
	GPIOA->ODR ^= ( 1 << 6);
    vTaskDelay(initDelay/portTICK_PERIOD_MS); 
    //BaseType_t 
    TickType_t waitTicks= pdMS_TO_TICKS(initDelay);     
    /*Va revisar lo que hay en la cola de xperiodqueue cada inicialms*/
    if(xQueueReceive(xPeriodQueue, &receivedQueue, waitTicks) == pdPASS){ /*Es el & pa que envie el inicio del struct */
        if(receivedQueue < 1)
         receivedQueue = initialMs;            
    if(receivedQueue >= finalMs)
            receivedQueue = finalMs;                
    initdelay = receivedQueue;            
    }
}
void vTaskButton(void *pvParameters){
    (void) pvParameters;
    uint8_t lastState = 1 ; /*Test the last state*/
    uint32_t Period = initialMs;
    for(;;){
    uint8_t actualState = !(GPIOC->IDR & (1<<13)) ? 1 : 0;
    /*
    uint8_t actualState;    
    if(!(GPIOC->IDR & (1<<13)))
        actualState = 1;
    else 
        actualState = 0;
    */
        if((lastState == 1) && (actualState == 0)){
        vTaskDelay(pdMS_TO_TICKS(20)); /*20ms de rebote*/
        period += initialMs;
        
        if(xQueueSend(xPeriodQueue, &period, pdMS_TO_TICKS(10)) != pdPASS){
            uint32_t temp;
            if(xQueueReceive(xPeriodQueue, &temp, 0) == pdPASS){
                (void) xQueueSend(xPeriodQueue, &period, pdMS_TO_TICKS(10));
            }
        }
        
    lastState = actualState;
    vTaskDelay(pdMS_TO_TICKS(50)); /*50ms de espera*/
    }
}


void confRCC(void){
	/*Encendemos el clk en PA*/
	RCC->AHB1ENR |= (1 << 0);
	
}



void confGPIO(void){
  	GPIOA->MODER |= (5 <<10); /*A5 */
    GPIOE->PUPDR |= (0x1 <<10); /*Pull up in A8 */
    /*Button 8*/
	
	
}

