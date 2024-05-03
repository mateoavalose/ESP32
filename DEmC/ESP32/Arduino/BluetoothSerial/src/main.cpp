#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
String BLName = "ESP32_MA";

// Data to be sent and received. It can be defined as a int to work with the ASCII code
String UART_Data;
String BT_Data;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(BLName);
  Serial.println("Connect to bluetooth: " + BLName);
  delay(1000);
}

void loop() {
  if(Serial.available() > 0) {
    UART_Data = Serial.readStringUntil('\n'); // If working with ASCII: UART_Data = Serial.read();
    SerialBT.print("Data from UART with PC: ");
    SerialBT.println(UART_Data);
  }

  if(SerialBT.available() > 0) {
    BT_Data = SerialBT.readStringUntil('\n'); // If working with ASCII: BT_Data = SerialBT.read();
    Serial.print("Data from bluetooth: ");
    Serial.println(BT_Data);
  }
}