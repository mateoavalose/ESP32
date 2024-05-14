#include <Arduino.h>

int data [7];
int cont = 0;

void send_data(int data);

void setup() {
  Serial2.begin(9600);
}

void loop() {
  // Send data to n0 object
  send_data(cont);
  cont++;
  if(cont > 99)
    cont = 0;
  delay(100);
}

void send_data(int data) { // Sending data to n0 object
  Serial2.write('n');
  Serial2.write('0');
  Serial2.write('.');
  Serial2.write('v');
  Serial2.write('a');
  Serial2.write('l');
  Serial2.write('=');
  Serial2.print(cont);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  delay(1000);
}