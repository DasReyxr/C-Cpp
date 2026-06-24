#include <Arduino.h>

void setup() {
  // Initialize the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED ON (inverted logic)
  delay(1000);                     // Wait for 1 second
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED OFF
  delay(1000);                     // Wait for 1 second
}
