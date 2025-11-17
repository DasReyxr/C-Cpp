#include "TFT_ST7735.h"

/*

 A3 CS OUT
 A4 DC OUT
 A5 SCK AFR
 A6 RES OUT
 A7 MOSI AFR
 
*/

TFT_ST7735::TFT_ST7735() 
{
    //INIT();
}

TFT_ST7735::~TFT_ST7735() {
}
/*----------- Private Functions -----------*/
void TFT_ST7735::delay_ms(volatile uint32_t ms){
	while(ms--){
		for(volatile uint32_t i =0; i<1067;i++){
		}}
}

void TFT_ST7735::modeSel(uint8_t cmd){
    /* D/CX = 0 => Data
       D/CX = 1 => Command*/
    if (cmd<2)
    GPIOA->BSRR = (1 << (PIN_DC+16*cmd));
}

void TFT_ST7735::csSet(uint8_t csEn){
    csEn ^= (1<<1);
    if (csEn<2)
    GPIOA->BSRR = (1 << (PIN_CS+16*csEn));
}

void TFT_ST7735::rstSet(uint8_t rstEn){
    rstEn ^= (1<<1);
    if (rstEn<2)
    GPIOA->BSRR = (1 << (PIN_RST+16*rstEn));
}


void TFT_ST7735::spiWrite(uint8_t* DATA, uint16_t size){
    uint16_t sent = 0;
    while(sent<size){

    while(!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = DATA[sent];
    
    switch(DATA[sent]){
        case ST7735_SWRESET:
            delay_ms(150);
            break;
        case ST7735_SLPOUT:
            delay_ms(500);
            break;
        case ST7735_NORON:
            delay_ms(10);
            break;
        case ST7735_DISPON:
            delay_ms(100);
            break;
        default:
            break; 
    }
    sent++;
	}
}

void TFT_ST7735::spiWrite(uint8_t DATA){
    while(!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = DATA;
    
    switch(DATA){
        case ST7735_SWRESET:
            delay_ms(150);
            break;
        case ST7735_SLPOUT:
            delay_ms(500);
            break;
        case ST7735_NORON:
            delay_ms(10);
            break;
        case ST7735_DISPON:
            delay_ms(100);
            break;
        default:
            break; 
	}
}

/*----------- Public Functions -----------*/

void TFT_ST7735::WriteCommand(uint8_t* cmd, uint16_t size) {
    modeSel(DCX_CMD);
   // csSet(false);
    spiWrite(cmd, size);
 //   csSet(true);
}

void TFT_ST7735::WriteCommand(uint8_t cmd) {
    WriteCommand(&cmd, 1);  
}

/*
void TFT_ST7735::WriteCommand(uint8_t cmd) {
    modeSel(DCX_CMD);
   // csSet(false);
    spiWrite(cmd);
 //   csSet(true);
}
*/

void TFT_ST7735::WriteData(uint8_t* data, uint16_t size) {
    modeSel(DCX_DATA);      
//    csSet(false);
    spiWrite(data, size);
//    csSet(true);
}

void TFT_ST7735::INIT_FN(void) {
    // HW reset
    rstSet(false);
    delay_ms(5);
    rstSet(true);
    delay_ms(50);

    WriteCommand(init_cmd,sizeofinit);


}


void TFT_ST7735::SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint8_t data[4];

    WriteCommand(0x2A);        // Column addr
    data[0] = x0 >> 8;
    data[1] = x0 & 0xFF;
    data[2] = x1 >> 8;
    data[3] = x1 & 0xFF;
    WriteData(data, 4);

    WriteCommand(0x2B);        // Row addr
    data[0] = y0 >> 8;
    data[1] = y0 & 0xFF;
    data[2] = y1 >> 8;
    data[3] = y1 & 0xFF;
    WriteData(data, 4);

    WriteCommand(0x2C);        // RAM write
}

void TFT_ST7735::DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    SetAddressWindow(x, y, x, y);

    uint8_t buf[2];
    buf[0] = color >> 8;
    buf[1] = color & 0xFF;

    WriteData(buf, 2);
}

void TFT_ST7735::WriteChar(uint16_t x, uint16_t y, char ch, FontDef font,
                           uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;

    uint16_t w = font.width;
    uint16_t h = font.height;

    for (i = 0; i < h; i++) {
        b = font.data[(ch - 32) * h + i];
        for (j = 0; j < w; j++) {
            if (b & (1 << (w - j - 1))) {
                DrawPixel(x + j, y + i, color);
            } else {
                DrawPixel(x + j, y + i, bgcolor);
            }
        }
    }
}

void TFT_ST7735::WriteString(uint16_t x, uint16_t y, const char* str, FontDef font,
                             uint16_t color, uint16_t bgcolor)
{
    while (*str) {
        WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }
}
