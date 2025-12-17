#ifndef CONF_H
#define CONF_H
extern void config(void);
extern void confRCC(void);
extern void confGPIO(void);
extern void confADC(void);
extern void confDMA(void);
extern void confTIMER(void);
volatile uint16_t adc_buffer[];
#define ADC_BUFFER_SIZE 16 
#endif