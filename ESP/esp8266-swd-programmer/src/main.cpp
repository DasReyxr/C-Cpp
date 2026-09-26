#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include "webpage.h"
#include "config.h"
#include "swd.h"
#include "programmer.h"

ESP8266WebServer server(80);

// Estado global del programador
enum State { IDLE, PROGRAMMING, VERIFYING, DONE, ERROR_STATE };
State     gState    = IDLE;
size_t    gProgress = 0;
size_t    gTotal    = 0;
String    gMessage  = "Listo para programar";

// ─── HTML de la interfaz web ─────────────────────────────


// ─── Handlers del servidor ───────────────────────────────

void handleRoot() {
    server.send_P(200, "text/html", INDEX_HTML);
}

void handleStatus() {
    String stateStr;
    switch (gState) {
        case IDLE:        stateStr = "IDLE";        break;
        case PROGRAMMING: stateStr = "PROGRAMMING"; break;
        case VERIFYING:   stateStr = "VERIFYING";   break;
        case DONE:        stateStr = "DONE";        break;
        default:          stateStr = "ERROR";       break;
    }
    String json = "{\"state\":\"" + stateStr + "\","
                  "\"progress\":" + String(gProgress) + ","
                  "\"total\":"    + String(gTotal)    + ","
                  "\"message\":\"" + gMessage + "\"}";
    // Limpiar mensaje para no repetirlo
    gMessage = "";
    server.send(200, "application/json", json);
}

void handleUpload() {
    // Solo aceptar si estamos IDLE
    if (gState == PROGRAMMING || gState == VERIFYING) {
        server.send(409, "text/plain", "Programacion en curso");
        return;
    }

    HTTPUpload &upload = server.upload();

    if (upload.status == UPLOAD_FILE_START) {
        LittleFS.remove("/firmware.bin");
        File f = LittleFS.open("/firmware.bin", "w");
        if (!f) {
            server.send(500, "text/plain", "No se pudo abrir archivo");
            return;
        }
        f.close();
        Serial.printf("Recibiendo: %s\n", upload.filename.c_str());

    } else if (upload.status == UPLOAD_FILE_WRITE) {
        File f = LittleFS.open("/firmware.bin", "a");
        if (f) { f.write(upload.buf, upload.currentSize); f.close(); }

    } else if (upload.status == UPLOAD_FILE_END) {
        Serial.printf("Recibidos %u bytes\n", upload.totalSize);
        gTotal    = upload.totalSize;
        gProgress = 0;
        gState    = PROGRAMMING;
        gMessage  = "Iniciando programacion...";
    }
}

void handleUploadComplete() {
    server.send(200, "text/plain", "OK");
}

// ─── Tarea de programación (no bloqueante con yield) ─────

void runProgrammingTask() {
    if (gState != PROGRAMMING) return;

    File f = LittleFS.open("/firmware.bin", "r");
    if (!f) {
        gMessage = "Error: no se encontró firmware.bin";
        gState   = ERROR_STATE;
        return;
    }

    size_t size = f.size();
    uint8_t *buf = (uint8_t*) malloc(size);
    if (!buf) {
        gMessage = "Error: sin memoria RAM para el firmware";
        gState   = ERROR_STATE;
        f.close();
        return;
    }

    f.read(buf, size);
    f.close();

    Serial.printf("Firmware: %u bytes\n", size);

    // Inicializar SWD
    swd.begin();
    if (!programmer.begin()) {
        gMessage = String("Error SWD: ") + programmer.lastError();
        gState   = ERROR_STATE;
        free(buf);
        return;
    }

    // Borrar sectores necesarios
    gMessage = "Borrando flash...";
    if (!programmer.eraseForSize(size)) {
        gMessage = String("Error borrado: ") + programmer.lastError();
        gState   = ERROR_STATE;
        free(buf);
        return;
    }

    // Programar
    gMessage = "Programando...";
    auto progressCb = [](size_t w, size_t t) {
        gProgress = w;
        gTotal    = t;
    };

    if (!programmer.program(buf, size, progressCb)) {
        gMessage = String("Error programacion: ") + programmer.lastError();
        gState   = ERROR_STATE;
        free(buf);
        return;
    }

    // Verificar
    gState   = VERIFYING;
    gMessage = "Verificando...";
    gProgress = 0;

    if (!programmer.verify(buf, size, progressCb)) {
        gMessage = String("Error verificacion: ") + programmer.lastError();
        gState   = ERROR_STATE;
        free(buf);
        return;
    }

    free(buf);

    // Resetear target y finalizar
    programmer.finalize();

    gProgress = gTotal;
    gState    = DONE;
    gMessage  = "¡Programación exitosa! STM32F401 reiniciado.";
    Serial.println("DONE");
}

// ─── Setup ───────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    Serial.println("\nESP8266 SWD Programmer arrancando...");

    if (!LittleFS.begin()) {
        Serial.println("ERROR: LittleFS no pudo montarse");
        while (true) delay(1000);
    }

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500); Serial.print(".");
    }
    Serial.println();
    Serial.print("IP: "); Serial.println(WiFi.localIP());

    // Rutas del servidor
    server.on("/",        HTTP_GET,  handleRoot);
    server.on("/status",  HTTP_GET,  handleStatus);
    server.on("/upload",  HTTP_POST, handleUploadComplete, handleUpload);

    server.begin();
    Serial.println("Servidor HTTP listo");
    Serial.printf("Abre http://%s en tu navegador\n",
                  WiFi.localIP().toString().c_str());
}

// ─── Loop ────────────────────────────────────────────────

void loop() {
    server.handleClient();
    runProgrammingTask();   // ejecuta la programación si hay tarea pendiente
    yield();
}
