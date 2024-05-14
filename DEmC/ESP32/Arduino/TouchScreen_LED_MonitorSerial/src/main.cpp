#include <Arduino.h>

const int led = 23; 
int data [7];

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode(23, OUTPUT);
}

void loop() {
  // Read data and print to serial
  if(Serial2.available() > 0) {
    int i = 0;
    int j = 0;
    while(i < 7) {
      int j = Serial2.read();
      if(j == -1)
        continue;
      data[i] = j;
      Serial.println(data[i]);
      i++;
    }
    Serial.println("");

    if(data[3] == 1) {
      if(data[2] == 3)
        digitalWrite(23, HIGH);
      else if(data[2] == 4)
        digitalWrite(23, LOW);
    }
  }
}