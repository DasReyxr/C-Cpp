#ifndef CONF_H
#define CONF_H

#include <string.h>
#include <stm32f446xx.h>
//#include <arm_math.h>


extern void CAR_Speed(uint16_t);
extern void CAR_Direction(float);
extern void CAR_LeftFront(void);
extern void CAR_LeftBack(void);
extern void CAR_RightFront(void);
extern void CAR_RightBack(void);
extern void CAR_Back(void);
extern void CAR_Front(void);

extern void config(void);
extern void confRCC(void);
extern void confGPIO(void);
extern void confTIMER(void);
#endif
