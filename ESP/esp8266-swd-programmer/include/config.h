#pragma once

// ─── WiFi ────────────────────────────────────────────────
#define WIFI_SSID     "Academia Yamaha AGS"
#define WIFI_PASSWORD "AcademiaYamaha2024"

// ─── Pines SWD (NodeMCU v1) ──────────────────────────────
// D1 = GPIO5   D2 = GPIO4   D3 = GPIO0   D0 = GPIO16
#define PIN_SWCLK   5   // D1
#define PIN_SWDIO   4   // D2
#define PIN_NRST    0   // D3 (opcional, puede dejarse sin conectar)

// ─── Target STM32F401 ────────────────────────────────────
#define STM32F4_FLASH_BASE    0x08000000UL
#define STM32F4_FLASH_SIZE    (256 * 1024)   // 256 KB en F401CC
#define STM32F4_PAGE_SIZE     16384           // sectores de 16 KB (sector 0-3)
#define STM32F4_RAM_BASE      0x20000000UL

// Registros SWD/DAP
#define DP_IDCODE       0x00
#define DP_ABORT        0x00
#define DP_CTRL_STAT    0x04
#define DP_SELECT       0x08
#define DP_RDBUFF       0x0C

#define AP_CSW          0x00
#define AP_TAR          0x04
#define AP_DRW          0x0C
#define AP_IDR          0xFC

// Bits de control
#define CSYSPWRUPREQ    (1UL << 30)
#define CDBGPWRUPREQ    (1UL << 28)
#define CSYSPWRUPACK    (1UL << 31)
#define CDBGPWRUPACK    (1UL << 29)

// STM32F4 Flash controller
#define FLASH_BASE_ADDR 0x40023C00UL
#define FLASH_KEYR      (FLASH_BASE_ADDR + 0x04)
#define FLASH_SR        (FLASH_BASE_ADDR + 0x0C)
#define FLASH_CR        (FLASH_BASE_ADDR + 0x10)

#define FLASH_KEY1      0x45670123UL
#define FLASH_KEY2      0xCDEF89ABUL
#define FLASH_CR_LOCK   (1UL << 31)
#define FLASH_CR_PG     (1UL << 0)
#define FLASH_CR_SER    (1UL << 1)
#define FLASH_CR_SNB    (3UL << 3)   // sector number bits [6:3]
#define FLASH_CR_STRT   (1UL << 16)
#define FLASH_CR_PSIZE  (2UL << 8)   // x32 parallelism (VCC 2.7-3.6V)
#define FLASH_SR_BSY    (1UL << 16)

// STM32 core debug
#define DHCSR           0xE000EDF0UL
#define DEMCR           0xE000EDFCUL
#define AIRCR           0xE000ED0CUL
#define DHCSR_DBGKEY    0xA05F0000UL
#define DHCSR_C_HALT    (1UL << 1)
#define DHCSR_C_DEBUGEN (1UL << 0)
#define AIRCR_SYSRESETREQ (1UL << 2)
#define AIRCR_VECTKEY   0x05FA0000UL
