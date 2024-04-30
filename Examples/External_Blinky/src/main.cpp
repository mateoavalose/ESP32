#include <Arduino.h>

void setup() {
  Serial.begin(115200); // initialize serial communication at 115200 bauds per second
  pinMode(GPIO_NUM_23, OUTPUT); // initialize LED digital pin as an output.
  Serial.println("Pin 23 initialized for output");
}

void loop() {
  digitalWrite(GPIO_NUM_23, HIGH); // turn the LED on
  delay(1000); // wait for a second (1000 milliseconds)
  digitalWrite(GPIO_NUM_23, LOW); // turn the LED off
  delay(1000);
}