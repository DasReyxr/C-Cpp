#ifndef I2C_H
#define I2C_H
#include <stm32f446xx.h>                      //EL LSB es para R/W
#define ADRS_LCDI2C (0X27<<1);/*0010 0111->0100 1110*/
extern void I2C_Write(uint8_t, uint8_t);
extern uint8_t I2C_Read(uint8_t,uint8_t*);
#endif