#include "ST7735.h"
#include "stm32f4xx.h"
#include <stdint.h>

void clock_init();
void gpio_init();
void spi1_init();

int main() {
    clock_init();
    gpio_init();
    spi1_init();

    TFT_ST7735 tft(
        &SPI1->DR,
        &SPI1->SR,
        SPI_SR_TXE,
        &GPIOA->BSRR, (1 << 4),   // PA4  CS
        &GPIOA->BSRR, (1 << 6),   // PA6  DC
        &GPIOA->BSRR, (1 << 5)    // PA5  RST
    );

    tft.Init();
    tft.FillScreen(0xFFFF);  // white
    tft.DrawPixel(10, 10, 0xF800); // red pixel
    tft.FillRect(20, 20, 40, 30, 0x07E0); // green block

    while (1) {
    }
}
