#include "TFT_ST7735.h"

TFT_ST7735::TFT_ST7735(
    void (*spiWriteFn)(const uint8_t* data, uint16_t size),
    void (*dcSetFn)(bool level),
    void (*csSetFn)(bool level),
    void (*rstSetFn)(bool level),
    void (*delayMsFn)(uint32_t ms)
) :
    _spiWrite(spiWriteFn),
    _dcSet(dcSetFn),
    _csSet(csSetFn),
    _rstSet(rstSetFn),
    _delayMs(delayMsFn)
{
}

TFT_ST7735::~TFT_ST7735() {
}

void TFT_ST7735::WriteCommand(uint8_t cmd) {
    _dcSet(false);     // command mode
    _csSet(false);
    _spiWrite(&cmd, 1);
    _csSet(true);
}

void TFT_ST7735::WriteData(const uint8_t* data, uint16_t size) {
    _dcSet(true);      // data mode
    _csSet(false);
    _spiWrite(data, size);
    _csSet(true);
}

void TFT_ST7735::Mode_Config(void) {
    // HW reset
    _rstSet(false);
    _delayMs(5);
    _rstSet(true);
    _delayMs(50);

    // ST7735 initialization sequence (common init)
    WriteCommand(0x01);   // SW reset
    _delayMs(150);

    WriteCommand(0x11);   // Sleep out
    _delayMs(120);

    // Pixel format: 16-bit
    WriteCommand(0x3A);
    {
        uint8_t d = 0x05;
        WriteData(&d, 1);
    }

    // Display ON
    WriteCommand(0x29);
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
