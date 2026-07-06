#pragma once
#include <Arduino.h>
#include "swd.h"

// Callback de progreso: recibe bytes escritos y total
typedef void (*ProgressCallback)(size_t written, size_t total);

class STM32Programmer {
public:
    // Inicializa, detiene el core y desbloquea flash
    bool begin();

    // Borra todos los sectores necesarios para 'size' bytes
    bool eraseForSize(size_t size);

    // Borra un sector específico (0-7 en F401)
    bool eraseSector(uint8_t sector);

    // Programa 'size' bytes desde 'data' en la flash del target
    bool program(const uint8_t *data, size_t size,
                 ProgressCallback cb = nullptr);

    // Verifica que la flash coincida con 'data'
    bool verify(const uint8_t *data, size_t size,
                ProgressCallback cb = nullptr);

    // Bloquea flash y resetea el target
    bool finalize();

    // Solo resetea sin reprogramar
    bool resetTarget();

    const char* lastError() { return _err; }

private:
    char _err[64] = {};

    bool haltCore();
    bool unlockFlash();
    bool lockFlash();
    bool waitFlashReady(uint32_t timeoutMs = 5000);
    uint8_t sectorForOffset(uint32_t offset);
    uint8_t sectorsNeeded(size_t size);

    void setError(const char *msg);
};

extern STM32Programmer programmer;
