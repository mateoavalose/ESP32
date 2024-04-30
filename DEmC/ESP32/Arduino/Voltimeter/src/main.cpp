#include <Arduino.h>

const int sensor = 34;
int ADC = 0;
float Vol = 0.0;
int mVol = 0;

void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);
}

void loop() {
  ADC = analogRead(sensor);
  Vol = ADC * (3.3 / 4095.0);
  mVol = Vol * 1000;
  Serial.print("\nADC: "); Serial.println(ADC);
  Serial.print(" Vol: "); Serial.println(Vol);
  Serial.print(" mVol: "); Serial.println(mVol);
  delay(1000);
}