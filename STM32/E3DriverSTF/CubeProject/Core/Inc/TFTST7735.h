/*
 * TFTST7735.h
 *
 *  Created on: Nov 2, 2025
 *      Author: dasre
 */


#ifndef INC_TFTST7735_H_
#define INC_TFTST7735_H_

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_GAMSET  0x26
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1




#include <stdint.h>
#include "fonts.h"  // Assuming FontDef lives here

class TFT_ST7735 {
public:
    TFT_ST7735(
        void (*spiWriteFn)(const uint8_t* data, uint16_t size),
        void (*dcSetFn)(bool level),
        void (*csSetFn)(bool level),
        void (*rstSetFn)(bool level),
        void (*delayMsFn)(uint32_t ms)
    );

    void Mode_Config(void);
    void DrawPixel(uint16_t x, uint16_t y, uint16_t color);

    void WriteChar(uint16_t x, uint16_t y, char ch, FontDef font,
                   uint16_t color, uint16_t bgcolor);

    void WriteString(uint16_t x, uint16_t y, const char* str, FontDef font,
                     uint16_t color, uint16_t bgcolor);

    void WriteData(const uint8_t* data, uint16_t size);

    virtual ~TFT_ST7735();

private:
    void (*_spiWrite)(const uint8_t*, uint16_t);
    void (*_dcSet)(bool);
    void (*_csSet)(bool);
    void (*_rstSet)(bool);
    void (*_delayMs)(uint32_t);

    void WriteCommand(uint8_t cmd);
    void SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
};

#endif
