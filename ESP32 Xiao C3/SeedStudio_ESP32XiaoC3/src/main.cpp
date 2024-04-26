#include <Arduino.h>

int led = 10; // the PWM pin the LED is attached to
int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by

void setup()
{
  Serial.begin(115200); // set up Serial library at 115200 bps
  pinMode(led, OUTPUT); // initialize LED digital pin as an output.
  Serial.println("Pin 10 initialized for PWM output.");
}

void loop()
{
  // set the brightness of pin 9:
  analogWrite(led, brightness);
 
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
 
  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  Serial.print("The LED Brightness is at: ");
  Serial.println(brightness);
  delay(10);
}