#include <Arduino.h>
#include "BluetoothSerial.h"

// Pin Definitions
// Sensors
const int LM35 = 26;
const int Photoresistor = 27;
// Actuators
const int Relay = 21;
const int Motor = 19;
const int PowerLED = 18;
// HMI - Bluetooth
BluetoothSerial SerialBT;
String BLName = "ESP32_MAE";

// Variables
int tempSensor;
int tempControl = 25;

int lightSensor;

String BT_Data;
int HMI_Data [7];

// Functions
int readTempSensor();
int readLightSensor();
int readBluetooth();
void readHMI();
void controlRelay(int num);
void controlMotor(int num);
void controlPowerLED(int num);
void updateHMI_int(String identifier, int value);
void updateHMI_txt(String identifier, String text);

void setup() {
  // Pin Initialization
  // Sensors
  pinMode(LM35, INPUT);
  pinMode(Photoresistor, INPUT);
  // Actuators
  pinMode(Relay, OUTPUT);

  ledcSetup(0, 5000, 10); // Channel, frequency, resolution
  ledcAttachPin(Motor, 0);

  ledcSetup(1, 5000, 10); // Channel, frequency, resolution
  ledcAttachPin(PowerLED, 1);

  // HMI - Nextion Initialization
  Serial2.begin(9600);
  // Bluetooth Initialization
  SerialBT.begin(BLName);
  delay(1000);
  updateHMI_txt("t11", BLName);
  delay(1000);
  // Update control data
  updateHMI_int("n1", tempControl);
  SerialBT.println("Temperature: " + String(tempControl) + " C");
}

void loop() {
  // ## Temperature control ##
  // Read sensor
  tempSensor = readTempSensor();
  if(tempSensor > 35) tempSensor = 35;
  updateHMI_int("n0", tempSensor);
  // Read control variables
  if(SerialBT.available() > 0) {
    tempControl = readBluetooth();
  } else if(Serial2.available() > 0) {
    readHMI();
  }
  updateHMI_int("n1", tempControl);
  // Control actuators
  if(tempControl - 1 <= tempSensor && tempSensor <= tempControl + 1) {
    controlRelay(0);
    updateHMI_txt("t2", "OFF");
    controlMotor(0);
    updateHMI_txt("t4", "OFF");
  } else if(tempSensor < tempControl - 1) {
    controlRelay(1);
    updateHMI_txt("t2", "ON");
    controlMotor(0);
    updateHMI_txt("t4", "OFF");
  } else if(tempControl + 1 < tempSensor && tempSensor < tempControl + 3) {
    controlRelay(0);
    updateHMI_txt("t2", "OFF");
    controlMotor(50); // 50% duty cycle
    updateHMI_txt("t4", "50%");
  } else if(tempControl + 3 <= tempSensor && tempSensor <= tempControl + 5) {
    controlRelay(0);
    updateHMI_txt("t2", "OFF");
    controlMotor(80); // 80% duty cycle
    updateHMI_txt("t4", "80%");
  } else if(tempSensor > tempControl + 5) {
    controlRelay(0);
    updateHMI_txt("t2", "OFF");
    controlMotor(100); // 100% duty cycle
    updateHMI_txt("t4", "100%");
  }
  // ## Light control ##
  // Read sensor
  lightSensor = readLightSensor();
  updateHMI_int("n2", lightSensor);
  // Control actuators
  if(lightSensor < 20) {
    controlPowerLED(100); // 100% duty cycle
    updateHMI_txt("t6", "100%");
  } else if(20 < lightSensor && lightSensor < 30) {
    controlPowerLED(80); // 80% duty cycle
    updateHMI_txt("t6", "80%");
  } else if (30 < lightSensor && lightSensor < 40) {
    controlPowerLED(60); // 60% duty cycle
    updateHMI_txt("t6", "60%");
  } else if (40 < lightSensor && lightSensor < 60) {
    controlPowerLED(50); // 50% duty cycle
    updateHMI_txt("t6", "50%");
  } else if (60 < lightSensor && lightSensor < 80) {
    controlPowerLED(30); // 30% duty cycle
    updateHMI_txt("t6", "30%");
  } else if (80 < lightSensor) {
    controlPowerLED(0); // 0% duty cycle
    updateHMI_txt("t6", "OFF");
  }
  delay(100);
}

// Function Definitions
int readTempSensor() {
  float ADC = 0;
  for(int i = 0; i < 100; i++) {
    ADC += analogRead(LM35);
    delay(10);
  }
  ADC /= 100;
  return (ADC * (3300.0 / 4095.0) / 10.0);
}

int readLightSensor() {
  float ADC = analogRead(Photoresistor);
  return (1 - (ADC / 4095.0)) * 100;
}

int readBluetooth() {
  BT_Data = SerialBT.readStringUntil('\n');
  SerialBT.println("Control temperature: " + BT_Data + " C");
  return BT_Data.toInt();
}

void readHMI() {
  int i = 0;
  while(i < 7) {
    int read = Serial2.read();
    if(read == -1)
      continue;
    HMI_Data[i] = read;
    i++;
    delay(10);
  }

  if(HMI_Data[3] == 1) {
    if(HMI_Data[2] == 12)
      tempControl += 1;
    else if(HMI_Data[2] == 13)
      tempControl -= 1;
  }
}

void controlRelay(int num) {
  digitalWrite(Relay, num);
}

void controlMotor(int num) {
  int dutyCycle = num * (1023.0 / 100);
  ledcWrite(0, dutyCycle);
}

void controlPowerLED(int num) {
  int dutyCycle = num * (1023.0 / 100);
  ledcWrite(1, dutyCycle);
}

void updateHMI_int(String identifier, int value) {
  String command = identifier + ".val=" + value;
  Serial2.print(command);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  delay(100);
}

void updateHMI_txt(String identifier, String text) {
  String command = identifier + ".txt=\"" + text + "\"";
  Serial2.print(command);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  delay(100);
}