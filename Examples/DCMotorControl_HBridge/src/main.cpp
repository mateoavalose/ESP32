#include <Arduino.h>

// Motor A
int motorPin1 = 27; 
int motorPin2 = 26; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
int dutyCycle = 200;

void setup() {
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motorPin1, pwmChannel1);
  ledcAttachPin(motorPin2, pwmChannel2);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  ledcWrite(pwmChannel1, 255);
  ledcWrite(pwmChannel2, 0);
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  ledcWrite(pwmChannel1, 0);
  ledcWrite(pwmChannel2, 0);
  delay(2000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  ledcWrite(pwmChannel1, 0);
  ledcWrite(pwmChannel2, 255);
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  ledcWrite(pwmChannel1, 0);
  ledcWrite(pwmChannel2, 0);
  delay(2000);

  // Move DC motor forward with increasing speed
  ledcWrite(pwmChannel2, 0);
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel1, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  delay(2000);
  dutyCycle = 200;
}