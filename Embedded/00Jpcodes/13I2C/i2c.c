/*
--------- Auf Das  ---------
---------- I2C  ----------
-------- 18/11/2025 --------

*/
// ------- Main Library -------
#include "i2c.h"

void I2C_Write(uint8_t add,uint8_t data){
    I2C1->CR1|=(1<<8);//Generamos el START
    while(!(I2C1->CR1 & I2C_SR1_SB));//ESPERO A QUE SE GENERO EL START
    I2C1->DR = add;
    while(!(I2C1->SR1 & I2C_SR1_ADDR));//ESPERO A QUE SE ENVIE LA DIRECCION
    (void)I2C1->SR2;
    /*if(I2C1->SR1 & I2C_SR1_AF){//pregunto si se genero un error por acknolage
    I2C1->CR1|=I2C_CR1_STOP;//DETENEMOS LA TRANSMISION
    }*/
    while(!(I2C1->SR1 & I2C_SR1_TXE));//Corroboramos la Transmision de datos y esperamos a que la transmision temrine
   I2C1->DR = data;
   while(!(I2C1->SR1 & I2C_SR1_BTF));
   /*generamos condición de stop*/
   I2C1->CR1|=I2C_CR1_STOP;
}