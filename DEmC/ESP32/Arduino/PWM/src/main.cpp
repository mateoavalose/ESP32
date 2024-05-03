#include <Arduino.h>

int duty_cycle = 0;

void setup() {
  ledcSetup(0, 5000, 8); // Channel, frequency, resolution
  ledcAttachPin(23, 0); 

  Serial.begin(115200);
  delay(1000);
}

void loop() {
  ledcWrite(0, duty_cycle);
  Serial.println(duty_cycle);

  duty_cycle += 1/*5*/;
  if(duty_cycle > 255) {
    duty_cycle = 0;
  }
  delay(50);
}