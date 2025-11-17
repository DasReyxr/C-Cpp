#ifndef CONF_H
#define CONF_H
#include <stm32f446xx.h>
extern void config(void);
extern void confRCC(void);
extern void confGPIO(void);
extern void confSPI(void);

extern void confUSART(void);
#define LED_ON 0X3A
#define LED_OFF 0XA3
#endif
