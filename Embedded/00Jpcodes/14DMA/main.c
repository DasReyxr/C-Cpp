#include "conf.h"
#include <stm32f446xx.h>

int main(void){
    config();
    while (1)
    {
        uint32_t sum =0;
        for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++)
        {
            sum+=adc_buffer[i];
        }
        uint32_t prom=sum/ADC_BUFFER_SIZE;
    }
}