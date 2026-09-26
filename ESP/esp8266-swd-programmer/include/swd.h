#pragma once
#include <Arduino.h>
#include "config.h"

// ─── Resultado de operaciones SWD ────────────────────────
enum SWDResult {
    SWD_OK = 0,
    SWD_FAULT,
    SWD_WAIT,
    SWD_ERROR,
    SWD_TIMEOUT
};

// ─── Clase principal del protocolo SWD ───────────────────
class SWDProtocol {
public:
    void    begin();
    void    lineReset();
    bool    connect();          // conecta y enciende el DAP
    void    disconnect();

    // Registro DP (Debug Port)
    SWDResult readDP(uint8_t addr, uint32_t &val);
    SWDResult writeDP(uint8_t addr, uint32_t val);

    // Registro AP (Access Port)
    SWDResult readAP(uint8_t addr, uint32_t &val);
    SWDResult writeAP(uint8_t addr, uint32_t val);

    // Memoria del target
    SWDResult readMem32(uint32_t addr, uint32_t &val);
    SWDResult writeMem32(uint32_t addr, uint32_t val);

    // Bloque de memoria
    SWDResult writeMemBlock(uint32_t addr, const uint8_t *data, size_t len);

    uint32_t getIDCODE() { return _idcode; }

private:
    uint32_t _idcode = 0;

    // Primitivas de bit-bang
    inline void    clkHigh()   { digitalWrite(PIN_SWCLK, HIGH); }
    inline void    clkLow()    { digitalWrite(PIN_SWCLK, LOW);  }
    inline void    dioHigh()   { digitalWrite(PIN_SWDIO, HIGH); }
    inline void    dioLow()    { digitalWrite(PIN_SWDIO, LOW);  }
    inline void    dioInput()  { pinMode(PIN_SWDIO, INPUT);     }
    inline void    dioOutput() { pinMode(PIN_SWDIO, OUTPUT);    }
    inline uint8_t dioRead()   { return digitalRead(PIN_SWDIO); }

    void     writeBit(uint8_t bit);
    uint8_t  readBit();
    void     writeBits(uint32_t val, int n);
    uint32_t readBits(int n);
    uint8_t  parity32(uint32_t val);

    // Transferencia SWD
    SWDResult transfer(uint8_t APnDP, uint8_t RnW, uint8_t addr,
                       uint32_t &data);
    void      selectAP(uint8_t apAddr);
    SWDResult waitBusy();
};

extern SWDProtocol swd;
