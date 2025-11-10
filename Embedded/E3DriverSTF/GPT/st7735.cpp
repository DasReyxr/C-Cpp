#include "TFT_ST7735.h"
#include <string.h>

// Command lists from your C code
#define DELAY 0x80

static const uint8_t init_cmds1[] = {
    15,
    ST7735_SWRESET, DELAY,
      150,
    ST7735_SLPOUT, DELAY,
      255,
    ST7735_FRMCTR1, 3,
      0x01, 0x2C, 0x2D,
    ST7735_FRMCTR2, 3,
      0x01, 0x2C, 0x2D,
    ST7735_FRMCTR3, 6,
      0x01, 0x2C, 0x2D,
      0x01, 0x2C, 0x2D,
    ST7735_INVCTR, 1,
      0x07,
    ST7735_PWCTR1, 3,
      0xA2,
      0x02,
      0x84,
    ST7735_PWCTR2, 1,
      0xC5,
    ST7735_PWCTR3, 2,
      0x0A, 0x00,
    ST7735_PWCTR4, 2,
      0x8A, 0x2A,
    ST7735_PWCTR5, 2,
      0x8A, 0xEE,
    ST7735_VMCTR1, 1,
      0x0E,
    ST7735_INVOFF, 0,
    ST7735_MADCTL, 1,
      ST7735_ROTATION,
    ST7735_COLMOD, 1,
      0x05
};

static const uint8_t init_cmds2[] = {
    2,
    ST7735_CASET, 4,
      0x00, 0x00,
      0x00, 0x7F,
    ST7735_RASET, 4,
      0x00, 0x00,
      0x00, 0x7F
};

static const uint8_t init_cmds3[] = {
    4,
    ST7735_GMCTRP1, 16,
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16,
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON, DELAY,
      10,
    ST7735_DISPON, DELAY,
      100
};


TFT_ST7735::TFT_ST7735(
    SpiWriteCb spi,
    GpioWriteCb dc,
    GpioWriteCb cs,
    GpioWriteCb rst,
    DelayCb delay
) :
    _spiWrite(spi),
    _dcSet(dc),
    _csSet(cs),
    _rstSet(rst),
    _delayMs(delay)
{
}

TFT_ST7735::~TFT_ST7735() {}


// ---------------------------------------------------------
// Basic low-level helpers
// ---------------------------------------------------------
void TFT_ST7735::WriteCommand(uint8_t cmd) {
    _dcSet(false);
    _csSet(false);
    _spiWrite(&cmd, 1);
    _csSet(true);
}

void TFT_ST7735::WriteData(const uint8_t* data, uint16_t size) {
    _dcSet(true);
    _csSet(false);
    _spiWrite(data, size);
    _csSet(true);
}


void TFT_ST7735::Reset() {
    _rstSet(false);
    _delayMs(5);
    _rstSet(true);
    _delayMs(5);
}


// ---------------------------------------------------------
// Execute Adafruit-style command list
// ---------------------------------------------------------
void TFT_ST7735::ExecuteCommands(const uint8_t* addr) {
    uint8_t numCommands = *addr++;

    while (numCommands--) {
        uint8_t cmd = *addr++;
        WriteCommand(cmd);

        uint8_t numArgs = *addr++;
        uint16_t ms = numArgs & DELAY;
        numArgs &= ~DELAY;

        if (numArgs) {
            WriteData(addr, numArgs);
            addr += numArgs;
        }

        if (ms) {
            ms = *addr++;
            if (ms == 255) ms = 500;
            _delayMs(ms);
        }
    }
}


// ---------------------------------------------------------
// Initialization
// ---------------------------------------------------------
void TFT_ST7735::Init() {
    _csSet(false);
    Reset();

    ExecuteCommands(init_cmds1);
    ExecuteCommands(init_cmds2);
    ExecuteCommands(init_cmds3);

    _csSet(true);
}


// ---------------------------------------------------------
// Address window
// ---------------------------------------------------------
void TFT_ST7735::SetAddressWindow(
    uint16_t x0, uint16_t y0,
    uint16_t x1, uint16_t y1
) {
    uint8_t data[4];

    WriteCommand(ST7735_CASET);
    data[0] = x0 >> 8;
    data[1] = x0 & 0xFF;
    data[2] = x1 >> 8;
    data[3] = x1 & 0xFF;
    WriteData(data, 4);

    WriteCommand(ST7735_RASET);
    data[0] = y0 >> 8;
    data[1] = y0 & 0xFF;
    data[2] = y1 >> 8;
    data[3] = y1 & 0xFF;
    WriteData(data, 4);

    WriteCommand(ST7735_RAMWR);
}


// ---------------------------------------------------------
// DrawPixel
// ---------------------------------------------------------
void TFT_ST7735::DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= ST7735_WIDTH || y >= ST7735_HEIGHT) return;

    SetAddressWindow(x, y, x, y);

    uint8_t c[2] = { (uint8_t)(color >> 8), (uint8_t)(color & 0xFF) };
    WriteData(c, 2);
}


// ---------------------------------------------------------
// Character / string rendering
// ---------------------------------------------------------
void TFT_ST7735::WriteChar(
    uint16_t x, uint16_t y, char ch,
    FontDef font, uint16_t color, uint16_t bgcolor
) {
    uint32_t i, j, row;
    SetAddressWindow(x, y, x + font.width - 1, y + font.height - 1);

    for (i = 0; i < font.height; i++) {
        row = font.data[(ch - 32) * font.height + i];

        for (j = 0; j < font.width; j++) {
            uint16_t c = (row << j) & 0x8000 ? color : bgcolor;
            uint8_t pix[2] = { c >> 8, c & 0xFF };
            WriteData(pix, 2);
        }
    }
}

void TFT_ST7735::WriteString(
    uint16_t x, uint16_t y, const char* str,
    FontDef font, uint16_t color, uint16_t bgcolor
) {
    while (*str) {
        if (x + font.width >= ST7735_WIDTH) {
            x = 0;
            y += font.height;
            if (y + font.height >= ST7735_HEIGHT) return;
        }
        WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }
}
