#ifndef CONF_H
#define CONF_H
#include <stm32f446xx.h>
extern void config(void);
extern void confRCC(void);
extern void confGPIO(void);
extern void confSPI(void);
#define LED_ON (uint8_t)0X3AU
#define LED_OFF (uint8_t)0XA3U
#endif
