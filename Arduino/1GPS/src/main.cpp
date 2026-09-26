#include <Arduino.h>
#include <TinyGPS++.h>

static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

unsigned long lastPrint = 0;

void setup() {
    Serial.begin(9600);
    Serial3.begin(GPSBaud);

    Serial.println("Iniciando GPS...");
}

void loop() {

    while (Serial3.available() > 0) {
        char c = Serial3.read();

        Serial.write(c);  // Mostrar NMEA crudo
        gps.encode(c);

        // Descomenta para ver NMEA crudo
        // Serial.write(c);
    }

    if (millis() - lastPrint >= 5000) {

        lastPrint = millis();

        Serial.println();
        Serial.println("========== GPS ==========");

        Serial.print("Caracteres procesados: ");
        Serial.println(gps.charsProcessed());

        Serial.print("Checksum OK: ");
        Serial.println(gps.passedChecksum());

        Serial.print("Checksum fallido: ");
        Serial.println(gps.failedChecksum());

        Serial.print("Satélites: ");

        if (gps.satellites.isValid())
            Serial.println(gps.satellites.value());
        else
            Serial.println("No valido");

        Serial.print("HDOP: ");

        if (gps.hdop.isValid())
            Serial.println(gps.hdop.hdop());
        else
            Serial.println("No valido");

        Serial.print("Ubicacion: ");

        if (gps.location.isValid()) {

            Serial.print("Latitud: ");
            Serial.println(gps.location.lat(), 6);

            Serial.print("Longitud: ");
            Serial.println(gps.location.lng(), 6);

        } else {

            Serial.println("SIN FIX");

        }

        Serial.print("Edad de ubicacion: ");
        Serial.println(gps.location.age());

        Serial.println("=========================");
    }
}