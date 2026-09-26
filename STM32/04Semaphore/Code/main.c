/*
------ Orlando Reyes ------
--------- Auf Das ---------
------- Semaphores ---------
-------- 09/22/2025 --------
LED RED A0, 
LED GREEN A1, 
LED YELLOW A2
BUTTON E8
We would generate three task that would be handle by a semaphore


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
#define RED 0
#define GREEN 1
#define YELLOW 2
void confRCC(void);
void confGPIO(void);
// --------- Function ---------
// ---- Administradores ----
QueueHandle_t xSEMQueue = NULL;
QueueHandle_t xCONTROLQueue = NULL;

SemaphoreHandle_t SemaphoreRED = NULL;
SemaphoreHandle_t SemaphoreGREEN = NULL;
SemaphoreHandle_t SemaphoreYELLOW = NULL;
SemaphoreHandle_t SemaphoreBLINK = NULL;


TaskHandle_t LEDRHandle;
TaskHandle_t LEDGHandle;
TaskHandle_t LEDYHandle;
TaskHandle_t BlinkHandle;
TaskHandle_t ButtonHandle;

void vTaskLEDR(void *);
void vTaskLEDG(void *);
void vTaskLEDY(void *);

void vTaskBlink(void *);
void vTaskButton(void *);

// ---------- Class ----------
// -------- Variables --------
// ----------- Main -----------

	
int main(void){
	confRCC(); /*Llamada de la funcion*/
	confGPIO();


    /*Create Tasks*/
    xCONTROLQueue= xQueueCreate( 1, sizeof( uint8_t ) );
    xSEMQueue   = xQueueCreate( 1, sizeof( uint8_t ) );
    SemaphoreRED = xSemaphoreCreateBinary();
    SemaphoreGREEN = xSemaphoreCreateBinary();
    SemaphoreYELLOW = xSemaphoreCreateBinary();
    SemaphoreBLINK = xSemaphoreCreateBinary();
    xSemaphoreGive(SemaphoreRED);
   
    xTaskCreate(vTaskButton, "Task Button", 100, NULL, 3, &ButtonHandle);
    xTaskCreate(vTaskBlink, "Task Blink", 100, NULL, 2, &BlinkHandle);
    xTaskCreate(vTaskLEDR, "Task LEDR", 100, NULL, 1, &LEDRHandle);
    xTaskCreate(vTaskLEDG, "Task LEDG", 100, NULL, 1, &LEDGHandle);
    xTaskCreate(vTaskLEDY, "Task LEDY", 100, NULL, 1, &LEDYHandle);

    /*Created*/
    vTaskStartScheduler();

    while(1);

}



void vTaskLEDR(void *pvParameters){
    uint8_t recievedQueue;
  while(1){
		xSemaphoreTake(SemaphoreRED, portMAX_DELAY);
		GPIOA->ODR = ( 1 << RED);
    vTaskDelay(pdMS_TO_TICKS(5000));
    GPIOA->ODR = ( 0 << RED); 
		if((xQueueReceive(xSEMQueue,&recievedQueue,(pdMS_TO_TICKS (20))) == pdPASS) && (recievedQueue == 255)) 
	        xSemaphoreGive(SemaphoreBLINK);
		else
			xSemaphoreGive(SemaphoreGREEN);	
	}
}

void vTaskLEDG(void *pvParameters){
    uint8_t recievedQueue;
while(1){
    xSemaphoreTake(SemaphoreGREEN, portMAX_DELAY);      
		GPIOA->ODR = ( 1 << GREEN);
    vTaskDelay(pdMS_TO_TICKS(3000));
    GPIOA->ODR = ( 0 << GREEN);
	if((xQueueReceive(xSEMQueue,&recievedQueue,(pdMS_TO_TICKS (10))) == pdPASS) && (recievedQueue == 255))
        xSemaphoreGive(SemaphoreBLINK);     
	else
	    xSemaphoreGive(SemaphoreYELLOW);
		
	}

}
void vTaskLEDY(void *pvParameters){ 
    uint8_t recievedQueue;

while(1){	
    xSemaphoreTake(SemaphoreYELLOW, portMAX_DELAY);
		 for(uint8_t i=0; i<9; i++){    
    GPIOA->ODR = ( 1 << YELLOW);
    vTaskDelay(pdMS_TO_TICKS(250));
    GPIOA->ODR = ( 0 << YELLOW); 
    vTaskDelay(pdMS_TO_TICKS(250));    
    }
	if((xQueueReceive(xSEMQueue,&recievedQueue,(pdMS_TO_TICKS (20))) == pdPASS) && (recievedQueue == 255))
        xSemaphoreGive(SemaphoreBLINK);
	else		
        xSemaphoreGive(SemaphoreRED); 
	
	}
}


void vTaskBlink(void *pvParameters){   
	  uint8_t sendstate =0; 
uint8_t recievedQueue;	
	while(1){
		xSemaphoreTake(SemaphoreBLINK, portMAX_DELAY);
		GPIOA->ODR &=(0XFFFFFF00);
		xQueueReceive(xCONTROLQueue,&sendstate,(pdMS_TO_TICKS (10)));
		while(sendstate == 0XFF )
		{
		GPIOA->ODR ^= ( 1 << YELLOW);
		GPIOA->ODR ^= ( 1 << RED);
		GPIOA->ODR ^= ( 1 << GREEN);
	    vTaskDelay(pdMS_TO_TICKS(500));
		if((xQueueReceive(xCONTROLQueue,&sendstate,(pdMS_TO_TICKS (10))) == pdPASS))
			sendstate = 5;
		}
		GPIOA->ODR &=(0XFFFFFF00);
		xQueueReset(xSEMQueue);
		xQueueReset(xCONTROLQueue);
		xSemaphoreGive(SemaphoreRED);
}
}


void vTaskButton(void *pvPARAMETERS){
    uint8_t lastState = 1;
	uint8_t cont =0;
	while(1){
		uint8_t actualState;
		if(!((GPIOE->IDR) & (1 << 8)))
			actualState = 0;
			else 
				actualState = 1;
			if(lastState ==1 && actualState == 0 )
			{
				vTaskDelay(pdMS_TO_TICKS(20));
        uint8_t sendstate = ~actualState;
				xQueueSend(xSEMQueue,&sendstate,portMAX_DELAY);
				xQueueSend(xCONTROLQueue,&sendstate,portMAX_DELAY);
				if(cont == 1){
				xQueueSend(xCONTROLQueue,&sendstate,portMAX_DELAY);
        		cont=0;
				}
				else
				cont+=1;
			}
			lastState= actualState;
	vTaskDelay(pdMS_TO_TICKS(50));
	}
}


void confRCC(void){
	/*Encendemos el clk en PA*/
	RCC->AHB1ENR |= (1 << 0)| (1 << 4); // A  E
	
}



void confGPIO(void){

  	GPIOA->MODER |= (0x15 <<0); /*A2 A1 A0*/	
    GPIOE->PUPDR |=(1<<16);//E8
}

