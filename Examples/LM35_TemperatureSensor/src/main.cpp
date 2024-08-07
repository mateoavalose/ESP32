#include <Arduino.h>

const int tempPin = 26;
int ADC = 0;
int mV = 0;
int temp = 0;

void setup() {
  Serial.begin(115200);
  pinMode(tempPin, INPUT);
}

void loop() {
  ADC = analogRead(tempPin);
  mV = ADC*(3300.0 / 4095.0);
  temp = mV / 10;
  Serial.print("\nADC: "); Serial.println(ADC);
  Serial.print(" mV: "); Serial.print(mV); Serial.println(" mV");
  Serial.print(" Temp: "); Serial.print(temp); Serial.println(" C");
  delay(1000);
}