#include <Arduino.h>

int cont = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(cont);
  cont++;
  delay(250);
  if(cont == 100) cont = 0;
}