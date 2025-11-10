#ifndef ST7735_H
#define ST7735_H

#include <stdint.h>

// Screen dimensions (edit for your model)
#define ST7735_WIDTH   128
#define ST7735_HEIGHT  160

// ST7735 Commands
#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT  0x11
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_INVON   0x21
#define ST7735_INVOFF  0x20

class TFT_ST7735 {
public:
    TFT_ST7735(volatile uint32_t* spiDR,
               volatile uint32_t* spiSR,
               uint32_t spiTXEflag,
               volatile uint32_t* gpioCS_BSRR,
               uint16_t csPin,
               volatile uint32_t* gpioDC_BSRR,
               uint16_t dcPin,
               volatile uint32_t* gpioRST_BSRR,
               uint16_t rstPin);

    void Init();
    void DrawPixel(uint16_t x, uint16_t y, uint16_t color);
    void FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
    void FillScreen(uint16_t color);

private:
    // low-level primitives
    void _cmd(uint8_t c);
    void _data(const uint8_t* data, uint16_t size);
    inline void _data8(uint8_t v);
    inline void _data16(uint16_t v);

    void _setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void _reset();
    inline void _select();
    inline void _unselect();

    // SPI raw transmit
    inline void _spiWrite(uint8_t v);

private:
    volatile uint32_t* _spiDR;
    volatile uint32_t* _spiSR;
    uint32_t _spiTXEflag;

    volatile uint32_t* _csBSRR;
    uint16_t _csPin;

    volatile uint32_t* _dcBSRR;
    uint16_t _dcPin;

    volatile uint32_t* _rstBSRR;
    uint16_t _rstPin;
};

#endif
