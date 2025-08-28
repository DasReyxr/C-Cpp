#ifndef CONF_H
#define CONF_H

#include <stm32f446xx.h>
/*Prototipado */
extern void confRCC(void);
extern void confGPIO(void);
extern void setClkHSE(void);
extern void setClkPLL(void);

#endif