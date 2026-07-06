#include "swd.h"

SWDProtocol swd;

// ─── Delay mínimo entre flancos (~1 MHz efectivo) ────────
#define SWD_DELAY() delayMicroseconds(1)

// ─── Primitivas de bit-bang ──────────────────────────────

void SWDProtocol::writeBit(uint8_t bit) {
    clkLow();
    SWD_DELAY();
    if (bit) dioHigh(); else dioLow();
    clkHigh();
    SWD_DELAY();
}

uint8_t SWDProtocol::readBit() {
    clkLow();
    SWD_DELAY();
    clkHigh();
    SWD_DELAY();
    return dioRead();
}

void SWDProtocol::writeBits(uint32_t val, int n) {
    for (int i = 0; i < n; i++) {
        writeBit((val >> i) & 1);   // LSB primero (SWD es LSB-first)
    }
}

uint32_t SWDProtocol::readBits(int n) {
    uint32_t val = 0;
    for (int i = 0; i < n; i++) {
        if (readBit()) val |= (1UL << i);
    }
    return val;
}

uint8_t SWDProtocol::parity32(uint32_t val) {
    val ^= val >> 16;
    val ^= val >> 8;
    val ^= val >> 4;
    val ^= val >> 2;
    val ^= val >> 1;
    return val & 1;
}

// ─── Inicialización ──────────────────────────────────────

void SWDProtocol::begin() {
    pinMode(PIN_SWCLK, OUTPUT);
    pinMode(PIN_SWDIO, OUTPUT);
    pinMode(PIN_NRST,  OUTPUT);
    digitalWrite(PIN_SWCLK, LOW);
    digitalWrite(PIN_SWDIO, HIGH);
    digitalWrite(PIN_NRST,  HIGH);
}

// ─── Line reset: 50+ ciclos con SWDIO=1, luego secuencia JTAG→SWD ──

void SWDProtocol::lineReset() {
    dioOutput();
    dioHigh();

    // 56 ciclos de reset
    for (int i = 0; i < 56; i++) writeBit(1);

    // Secuencia mágica JTAG→SWD: 0xE79E (16 bits, LSB first)
    writeBits(0xE79E, 16);

    // Otros 56 ciclos de reset
    for (int i = 0; i < 56; i++) writeBit(1);

    // 8 ciclos idle
    for (int i = 0; i < 8; i++) writeBit(0);
}

// ─── Transferencia SWD (corazón del protocolo) ───────────
//
//  Packet request: START(1) | APnDP(1) | RnW(1) | A[2:3](2) | PARITY(1) | STOP(0) | PARK(1)
//  ACK:            3 bits turnaround
//  DATA:           32 bits + parity
//
SWDResult SWDProtocol::transfer(uint8_t APnDP, uint8_t RnW,
                                uint8_t addr, uint32_t &data) {
    uint8_t req = 0;
    req |= 1;                          // START
    req |= (APnDP & 1) << 1;
    req |= (RnW   & 1) << 2;
    req |= ((addr >> 1) & 1) << 3;    // A[2]
    req |= ((addr >> 2) & 1) << 4;    // A[3]

    // Paridad del request (bits 1-4)
    uint8_t par = ((req >> 1) ^ (req >> 2) ^ (req >> 3) ^ (req >> 4)) & 1;
    req |= par << 5;
    req |= 0 << 6;                     // STOP
    req |= 1 << 7;                     // PARK

    // Enviar request
    dioOutput();
    writeBits(req, 8);

    // Turnaround (SWDIO pasa a entrada)
    dioInput();
    readBit();

    // Leer ACK (3 bits)
    uint8_t ack = readBits(3);

    if (ack == 0x1) {  // OK
        if (RnW) {
            // READ: recibir 32 bits + paridad
            data = readBits(32);
            uint8_t parIn = readBit();
            dioOutput();
            readBit();  // turnaround de vuelta
            if (parIn != parity32(data)) return SWD_ERROR;
        } else {
            // WRITE: turnaround, luego enviar datos
            dioOutput();
            readBit();   // turnaround
            writeBits(data, 32);
            writeBit(parity32(data));
            dioHigh();
        }
        return SWD_OK;

    } else if (ack == 0x2) {
        dioOutput();
        return SWD_WAIT;
    } else {
        dioOutput();
        return SWD_FAULT;
    }
}

// ─── DP / AP ─────────────────────────────────────────────

SWDResult SWDProtocol::readDP(uint8_t addr, uint32_t &val) {
    return transfer(0, 1, addr, val);
}

SWDResult SWDProtocol::writeDP(uint8_t addr, uint32_t val) {
    return transfer(0, 0, addr, val);
}

void SWDProtocol::selectAP(uint8_t apAddr) {
    // SELECT: APSEL=0, APBANKSEL según dirección
    uint32_t sel = (apAddr & 0xF0);
    writeDP(DP_SELECT, sel);
}

SWDResult SWDProtocol::readAP(uint8_t addr, uint32_t &val) {
    selectAP(addr);
    SWDResult r = transfer(1, 1, addr & 0x0C, val);
    if (r != SWD_OK) return r;
    // AP reads necesitan un extra read de RDBUFF para obtener el dato real
    return readDP(DP_RDBUFF, val);
}

SWDResult SWDProtocol::writeAP(uint8_t addr, uint32_t val) {
    selectAP(addr);
    return transfer(1, 0, addr & 0x0C, val);
}

// ─── Acceso a memoria del target ─────────────────────────

SWDResult SWDProtocol::readMem32(uint32_t addr, uint32_t &val) {
    SWDResult r;
    // CSW: tamaño word, auto-incremento off
    uint32_t csw = 0x23000052;
    r = writeAP(AP_CSW, csw); if (r != SWD_OK) return r;
    r = writeAP(AP_TAR, addr); if (r != SWD_OK) return r;
    r = readAP(AP_DRW, val);
    return r;
}

SWDResult SWDProtocol::writeMem32(uint32_t addr, uint32_t val) {
    SWDResult r;
    uint32_t csw = 0x23000052;
    r = writeAP(AP_CSW, csw); if (r != SWD_OK) return r;
    r = writeAP(AP_TAR, addr); if (r != SWD_OK) return r;
    r = writeAP(AP_DRW, val);
    return r;
}

SWDResult SWDProtocol::writeMemBlock(uint32_t addr,
                                     const uint8_t *data, size_t len) {
    SWDResult r;
    // CSW con auto-incremento de word
    uint32_t csw = 0x23000052 | (1 << 4);  // AddrInc=1 (packed)
    r = writeAP(AP_CSW, csw); if (r != SWD_OK) return r;
    r = writeAP(AP_TAR, addr); if (r != SWD_OK) return r;

    for (size_t i = 0; i < len; i += 4) {
        uint32_t word = 0;
        size_t remaining = len - i;
        size_t chunk = (remaining >= 4) ? 4 : remaining;
        memcpy(&word, data + i, chunk);
        r = transfer(1, 0, AP_DRW, word);
        if (r != SWD_OK) return r;
        if (i % 128 == 0) yield();  // dar tiempo al WDT del ESP8266
    }
    return SWD_OK;
}

// ─── Conexión y power-up ─────────────────────────────────

bool SWDProtocol::connect() {
    lineReset();

    // Leer IDCODE (siempre primera operación)
    if (readDP(DP_IDCODE, _idcode) != SWD_OK) return false;
    if ((_idcode & 1) == 0) return false;   // bit 0 debe ser 1

    // Power up
    uint32_t ctrl = CSYSPWRUPREQ | CDBGPWRUPREQ;
    if (writeDP(DP_CTRL_STAT, ctrl) != SWD_OK) return false;

    // Esperar ACK de power up
    uint32_t timeout = 1000;
    uint32_t stat = 0;
    do {
        if (readDP(DP_CTRL_STAT, stat) != SWD_OK) return false;
        delay(1);
    } while (--timeout && !(stat & (CSYSPWRUPACK | CDBGPWRUPACK)));

    return timeout > 0;
}

void SWDProtocol::disconnect() {
    // Apagar debug
    writeDP(DP_CTRL_STAT, 0);
    dioInput();
    clkLow();
}
