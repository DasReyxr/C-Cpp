#include "programmer.h"

STM32Programmer programmer;

void STM32Programmer::setError(const char *msg) {
    strncpy(_err, msg, sizeof(_err) - 1);
    Serial.println(msg);
}

// ─── Detener el core ARM ─────────────────────────────────

bool STM32Programmer::haltCore() {
    // Habilitar debug y halt
    uint32_t dhcsr = DHCSR_DBGKEY | DHCSR_C_DEBUGEN | DHCSR_C_HALT;
    if (swd.writeMem32(DHCSR, dhcsr) != SWD_OK) {
        setError("No se pudo detener el core");
        return false;
    }
    // Esperar que el core se detenga
    delay(10);
    uint32_t val = 0;
    swd.readMem32(DHCSR, val);
    return (val & (1 << 17)) != 0;  // S_HALT
}

// ─── Desbloquear flash ───────────────────────────────────

bool STM32Programmer::unlockFlash() {
    uint32_t cr = 0;
    swd.readMem32(FLASH_CR, cr);
    if (!(cr & FLASH_CR_LOCK)) return true;  // ya desbloqueada

    if (swd.writeMem32(FLASH_KEYR, FLASH_KEY1) != SWD_OK) {
        setError("Error escribiendo KEY1");
        return false;
    }
    if (swd.writeMem32(FLASH_KEYR, FLASH_KEY2) != SWD_OK) {
        setError("Error escribiendo KEY2");
        return false;
    }

    swd.readMem32(FLASH_CR, cr);
    if (cr & FLASH_CR_LOCK) {
        setError("Flash no se desbloqueó");
        return false;
    }
    return true;
}

bool STM32Programmer::lockFlash() {
    uint32_t cr = 0;
    swd.readMem32(FLASH_CR, cr);
    cr |= FLASH_CR_LOCK;
    return swd.writeMem32(FLASH_CR, cr) == SWD_OK;
}

// ─── Esperar que la flash esté lista ─────────────────────

bool STM32Programmer::waitFlashReady(uint32_t timeoutMs) {
    uint32_t start = millis();
    uint32_t sr = 0;
    do {
        swd.readMem32(FLASH_SR, sr);
        if (sr & (1 << 1)) { setError("Flash: EOP error"); return false; }
        if (sr & (1 << 4)) { setError("Flash: write protection error"); return false; }
        if (sr & (1 << 5)) { setError("Flash: programming error"); return false; }
        yield();
    } while ((sr & FLASH_SR_BSY) && (millis() - start < timeoutMs));

    if (sr & FLASH_SR_BSY) { setError("Flash timeout"); return false; }
    return true;
}

// ─── Mapa de sectores STM32F401 ──────────────────────────
// Sector 0: 16KB  0x08000000
// Sector 1: 16KB  0x08004000
// Sector 2: 16KB  0x08008000
// Sector 3: 16KB  0x0800C000
// Sector 4: 64KB  0x08010000
// Sector 5: 128KB 0x08020000
// Sector 6: 128KB 0x08040000
// Sector 7: 128KB 0x08060000

uint8_t STM32Programmer::sectorForOffset(uint32_t offset) {
    if (offset < 0x4000)  return 0;
    if (offset < 0x8000)  return 1;
    if (offset < 0xC000)  return 2;
    if (offset < 0x10000) return 3;
    if (offset < 0x20000) return 4;
    if (offset < 0x40000) return 5;
    if (offset < 0x60000) return 6;
    return 7;
}

uint8_t STM32Programmer::sectorsNeeded(size_t size) {
    return sectorForOffset(size > 0 ? size - 1 : 0) + 1;
}

// ─── Borrar un sector ────────────────────────────────────

bool STM32Programmer::eraseSector(uint8_t sector) {
    Serial.printf("  Borrando sector %d...\n", sector);

    if (!waitFlashReady()) return false;

    // Limpiar flags de error
    swd.writeMem32(FLASH_SR, 0xF2);

    // CR: SER + SNB + PSIZE (x32)
    uint32_t cr = FLASH_CR_SER | FLASH_CR_PSIZE | ((uint32_t)sector << 3);
    if (swd.writeMem32(FLASH_CR, cr) != SWD_OK) return false;

    cr |= FLASH_CR_STRT;
    if (swd.writeMem32(FLASH_CR, cr) != SWD_OK) return false;

    return waitFlashReady(10000);
}

bool STM32Programmer::eraseForSize(size_t size) {
    uint8_t numSectors = sectorsNeeded(size);
    Serial.printf("Borrando %d sector(es) para %u bytes\n", numSectors, size);
    for (uint8_t s = 0; s < numSectors; s++) {
        if (!eraseSector(s)) return false;
    }
    return true;
}

// ─── Inicializar programación ────────────────────────────

bool STM32Programmer::begin() {
    Serial.println("Conectando al target...");
    if (!swd.connect()) {
        setError("No se pudo conectar por SWD");
        return false;
    }
    Serial.printf("IDCODE: 0x%08X\n", swd.getIDCODE());

    if (!haltCore()) return false;
    Serial.println("Core detenido OK");

    if (!unlockFlash()) return false;
    Serial.println("Flash desbloqueada OK");

    return true;
}

// ─── Programar flash ─────────────────────────────────────

bool STM32Programmer::program(const uint8_t *data, size_t size,
                               ProgressCallback cb) {
    Serial.printf("Programando %u bytes...\n", size);

    if (!waitFlashReady()) return false;

    // Habilitar programación
    uint32_t cr = FLASH_CR_PG | FLASH_CR_PSIZE;
    if (swd.writeMem32(FLASH_CR, cr) != SWD_OK) return false;

    uint32_t addr = STM32F4_FLASH_BASE;
    size_t written = 0;

    while (written < size) {
        size_t chunk = size - written;
        if (chunk > 256) chunk = 256;   // bloques de 256 bytes para no saturar
        // Asegurar múltiplo de 4
        chunk = (chunk + 3) & ~3;
        if (written + chunk > size) chunk = size - written;

        if (swd.writeMemBlock(addr, data + written, chunk) != SWD_OK) {
            setError("Error escribiendo bloque");
            return false;
        }
        if (!waitFlashReady(2000)) return false;

        addr    += chunk;
        written += chunk;
        if (cb) cb(written, size);
        yield();
    }

    // Apagar PG
    swd.writeMem32(FLASH_CR, 0);
    return true;
}

// ─── Verificar ───────────────────────────────────────────

bool STM32Programmer::verify(const uint8_t *data, size_t size,
                              ProgressCallback cb) {
    Serial.println("Verificando...");
    uint32_t addr = STM32F4_FLASH_BASE;

    for (size_t i = 0; i < size; i += 4) {
        uint32_t expected = 0;
        size_t chunk = (size - i >= 4) ? 4 : (size - i);
        memcpy(&expected, data + i, chunk);

        uint32_t actual = 0;
        if (swd.readMem32(addr + i, actual) != SWD_OK) {
            setError("Error leyendo para verificar");
            return false;
        }
        if (actual != expected) {
            snprintf(_err, sizeof(_err),
                     "Verificacion fallo en 0x%08X: esperado 0x%08X, leido 0x%08X",
                     (unsigned)(addr + i), (unsigned)expected, (unsigned)actual);
            Serial.println(_err);
            return false;
        }
        if (cb && i % 256 == 0) cb(i, size);
        if (i % 512 == 0) yield();
    }
    if (cb) cb(size, size);
    return true;
}

// ─── Finalizar: bloquear y resetear ──────────────────────

bool STM32Programmer::finalize() {
    lockFlash();
    return resetTarget();
}

bool STM32Programmer::resetTarget() {
    Serial.println("Reseteando target...");
    // System reset via AIRCR
    uint32_t val = AIRCR_VECTKEY | AIRCR_SYSRESETREQ;
    swd.writeMem32(AIRCR, val);
    delay(100);
    swd.disconnect();
    return true;
}
