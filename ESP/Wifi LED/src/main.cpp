1#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "main.h"
// ─── CONFIGURATION ────────────────────────────────────────────────────────────
const char* WIFI_SSID     = "Das Hause";       // <-- change this
const char* WIFI_PASSWORD = "delUnoaldiez";   // <-- change this

const int LED_PIN = LED_BUILTIN;               // D4 (GPIO2) on NodeMCU — active LOW
                                               // Change to e.g. 5 (D1) for external LED

// ─── GLOBALS ──────────────────────────────────────────────────────────────────
ESP8266WebServer server(80);
bool ledState = false;

// ─── HELPERS ──────────────────────────────────────────────────────────────────
String buildPage() {
  String html = String(HTML_PAGE);

  if (ledState) {
    html.replace("%BULBCLASS%",  "is-on");
    html.replace("%FILL%",       "#f5c842");
    html.replace("%STROKE%",     "#f5c842");
    html.replace("%OPACITY%",    "1");
    html.replace("%STATUSCLASS%","is-on");
    html.replace("%DOTCLASS%",   "is-on");
    html.replace("%STATUSTEXT%", "ON");
    html.replace("%BTNCLASS%",   "turn-off");
    html.replace("%BTNLABEL%",   "Turn OFF");
  } else {
    html.replace("%BULBCLASS%",  "is-off");
    html.replace("%FILL%",       "#3a3b45");
    html.replace("%STROKE%",     "#3a3b45");
    html.replace("%OPACITY%",    "0.6");
    html.replace("%STATUSCLASS%","is-off");
    html.replace("%DOTCLASS%",   "");
    html.replace("%STATUSTEXT%", "OFF");
    html.replace("%BTNCLASS%",   "turn-on");
    html.replace("%BTNLABEL%",   "Turn ON");
  }

  html.replace("%GPIO%", String(LED_PIN));
  html.replace("%IP%",   WiFi.localIP().toString());
  return html;
}

void applyLed() {
  // LED_BUILTIN on NodeMCU is active-LOW; flip if you use an external active-HIGH LED
  digitalWrite(LED_PIN, ledState ? LOW : HIGH);
}

// ─── ROUTE HANDLERS ───────────────────────────────────────────────────────────
void handleRoot() {
  server.send(200, "text/html", buildPage());
}

void handleToggle() {
  ledState = !ledState;
  applyLed();
  // Redirect back to root so refreshing the page doesn't re-POST
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleNotFound() {
  server.sendHeader("Location", "/");
  server.send(303);
}

// ─── SETUP & LOOP ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(LED_PIN, OUTPUT);
  applyLed();   // start with LED off

  // Connect to WiFi
  Serial.printf("Connecting to %s", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Register routes
  server.on("/",       HTTP_GET,  handleRoot);
  server.on("/toggle", HTTP_POST, handleToggle);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started — open the IP above in your browser.");
}

void loop() {
  server.handleClient();
}
