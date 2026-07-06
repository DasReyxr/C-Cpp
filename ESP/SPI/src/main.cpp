#include <Arduino.h>
#include <SPI.h>

#define CS_PIN 15  // D8
#define FREQ 1000000
void setup() {
    Serial.begin(115200);
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);  // Deselect device

    SPI.begin();                 // MOSI=D7, MISO=D6, SCLK=D5
    SPI.setFrequency(FREQ);   // 1 MHz
    SPI.setDataMode(SPI_MODE0);  // CPOL=0, CPHA=0
    SPI.setBitOrder(MSBFIRST);
}

void spiTransfer(uint8_t *txBuf, uint8_t *rxBuf, size_t len) {
    digitalWrite(CS_PIN, LOW);
    for (size_t i = 0; i < len; i++) {
        rxBuf[i] = SPI.transfer(txBuf[i]);
    }
    digitalWrite(CS_PIN, HIGH);
}

void loop() {
    uint8_t tx[] = {0x01, 0x02, 0x03};
    uint8_t rx[3] = {0};

    spiTransfer(tx, rx, sizeof(tx));

    Serial.printf("RX: 0x%02X 0x%02X 0x%02X\n", rx[0], rx[1], rx[2]);
    delay(1000);
}