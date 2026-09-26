#include <Arduino.h>

#define PWRKEY 7

void setup() {
  pinMode(PWRKEY, OUTPUT);
  digitalWrite(PWRKEY, HIGH);

  Serial.begin(9600);   // PC <-> Mega
  Serial3.begin(9600);  // Mega <-> SIM7020E

  digitalWrite(PWRKEY, LOW);
  delay(1500);
  digitalWrite(PWRKEY, HIGH);
  delay(10000);

  Serial.println("Listo. Escribe comandos AT y presiona enter.");
}

void loop() {
  // PC -> módulo
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    Serial3.print(cmd);
    Serial3.print("\r\n");  // el SIM7020E espera CR+LF al final
  }

  // módulo -> PC
  if (Serial3.available()) {
    String resp = Serial3.readStringUntil('\n');
    Serial.println(resp);
  }
}