#ifndef CONF_H
#define CONF_H
#include <stm32f446xx.h>
extern void config(void);
extern void confRCC(void);
extern void confGPIO(void);
extern void confADC(void);
extern void confDAC(void);
extern void confTIMER(void);
#endif
