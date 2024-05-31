#include <Arduino.h>

// RGB LED Pins
const int RPin = 12;
const int GPin = 14;
const int BPin = 27;

// ADC Pin
const int lightSensorPin = 25;

// Variables
// Data received from the HMI
int HMI_Data [7]; // 0: Start, 1: Page, 2: Component, 3: Event, 4: Empty, 5: Empty, 6: Empty
// Data read from the light sensor (ADC)
int blueRead = 0;
int blueCal = 0;
int whiteRead = 0;
int whiteCal = 0;
int redRead = 0;
int redCal = 0;
// Reference error
float referenceError = 35;

// Function declarations
void readSensor(char type);
void turnOffLED(int delayTime);
void readHMI();
void updateHMI_int(String identifier, int data);

void setup() {
  // RGB LED
  pinMode(RPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);
  turnOffLED(100);
  // Light Sensor
  pinMode(lightSensorPin, INPUT);
  // HMI
  Serial2.begin(9600);
  delay(1000);
  // Initialize the HMI
  updateHMI_int("n0", 0);
  updateHMI_int("n1", 0);
  updateHMI_int("n2", 0);
  updateHMI_int("n3", 0);
  updateHMI_int("n4", 0);
  updateHMI_int("n5", 0);
  updateHMI_int("n6", 0);
}

void loop() {
  if(Serial2.available() > 0) {
    readHMI();
    if(HMI_Data[2] == 3)
      readSensor('c');
    else if(HMI_Data[2] == 4)
      readSensor('a');
  }
  delay(100);
}

// Function definitions
void readSensor(char type) {
  // Turn off the RGB LED
  turnOffLED(100);

  // Turn on blue
  digitalWrite(BPin, LOW);
  delay(1000);
  if(type == 'c') {
    blueCal = analogRead(lightSensorPin) * (100 / 4095.0);
  } else if(type == 'a') {
    blueRead = analogRead(lightSensorPin) * (100 / 4095.0);
  }
  turnOffLED(200);

  // Turn on white
  digitalWrite(RPin, LOW);
  digitalWrite(GPin, LOW);
  digitalWrite(BPin, LOW);
  delay(1000);
  if(type == 'c') {
    whiteCal = analogRead(lightSensorPin) * (100 / 4095.0);
  } else if(type == 'a') {
    whiteRead = analogRead(lightSensorPin) * (100 / 4095.0);
  }
  turnOffLED(200);

  // Turn on red
  digitalWrite(RPin, LOW);
  delay(1000);
  if(type == 'c') {
    redCal = analogRead(lightSensorPin) * (100 / 4095.0);
  } else if(type == 'a') {
    redRead = analogRead(lightSensorPin) * (100 / 4095.0);
  }
  turnOffLED(200);

  // Parse calibration and analysis
  if(type == 'c') {
    // Send the calibration data to the HMI
    updateHMI_int("n0", blueCal);
    updateHMI_int("n1", whiteCal);
    updateHMI_int("n2", redCal);
  } else if(type == 'a') {
    // Send the analysis data to the HMI
    updateHMI_int("n3", blueRead);
    float blueError = abs((blueRead - blueCal) / blueCal * 100);
    updateHMI_int("n4", whiteRead);
    float whiteError = abs((whiteRead - whiteCal) / whiteCal * 100);
    updateHMI_int("n5", redRead);
    float redError = abs((redRead - redCal) / redCal * 100);
    if(blueError > referenceError || whiteError > referenceError || redError > referenceError) {
      updateHMI_int("n6", 0);
    } else {
      updateHMI_int("n6", 1);
    }
  }
}

void turnOffLED(int delayTime) {
  digitalWrite(RPin, HIGH);
  digitalWrite(GPin, HIGH);
  digitalWrite(BPin, HIGH);
  delay(delayTime);
}

void readHMI(){
  int i = 0;
  while(i < 7) {
    int read = Serial2.read();
    if(read == -1)
      continue;
    HMI_Data[i] = read;
    i++;
    delay(10);
  }
}

void updateHMI_int(String identifier, int value) {
  String command = identifier + ".val=" + value;
  Serial2.print(command);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  delay(100);
}