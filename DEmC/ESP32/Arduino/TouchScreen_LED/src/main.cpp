#include <Arduino.h>

const int led = 23;

void setup() {
  Serial2.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  int data = Serial2.read();
  if (data == 3) {
    digitalWrite(led, HIGH);
  } else if (data == 4) {
    digitalWrite(led, LOW);
  }
}