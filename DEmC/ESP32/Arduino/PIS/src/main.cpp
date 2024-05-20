#include <Arduino.h>
#include "pitches.h"

// Sensors
const int pressureSensor = 27;
const int flexSensor = 26;

// Actuators
const int buzzer = 25;
const int Motor1 = 33;
const int Motor2 = 32;

// Variables
// Data received from the HMI
int data [7];
// Therapy states
enum State {Start, Therapy1, Therapy2};
State currentState = Start;
// Base therapy time in milliseconds (10 minutes)
int therapyTime = 600000;
// Pressure levels in kPa
const int lowPressure = 200;
const int mediumPressure = 300;
const int highPressure = 400;

// Function declarations
int readFlexSensor();
int readPressureSensor();
void updateHMI0();
void updateHMI1();
void updateHMI2();
int readTherapyTime();
int readTherapy();
void therapy1();
void therapy2(int level);
int selectLevel();
void buzzerMelody(int melody);

void setup() {
  Serial.begin(115200); // Debugging ############################
  Serial.println("Starting..."); // Debugging ############################
  // Sensors
  pinMode(pressureSensor, INPUT);
  pinMode(flexSensor, INPUT);
  // Actuators
  ledcSetup(0, 5000, 12); // Channel, frequency, resolution
  ledcAttachPin(Motor1, 0);
  ledcSetup(1, 5000, 12); // Channel, frequency, resolution
  ledcAttachPin(Motor2, 1);
  // HMI
  Serial2.begin(9600);
}

void loop() {
  switch(currentState) {
    case Start:
      Serial.println("Start"); // Debugging ############################
      Serial.println("Current therapy time: " + String(therapyTime / 60000.0) + " minutes"); // Debugging ############################
      Serial.println("press + to increase therapy time or - to decrease it. Press 1 to select therapy 1 and 2 to select therapy 2"); // Debugging ############################
      while(Serial.available() == 0); // Debugging ############################
      if(Serial.available() > 0) { // Debugging ############################
        char c = Serial.read();
        if(c == '+') {
          therapyTime += 60000;
        } else if(c == '-') {
          therapyTime -= 60000;
        } else if(c == '1') {
          currentState = Therapy1;
        } else if(c == '2') {
          currentState = Therapy2;
        }
      }
      
      /*if(Serial.available() > 0) {
        therapyTime = readTherapyTime();
        if(readTherapy() == 1) {
          currentState = Therapy1;
        } else {
          currentState = Therapy2;
        }
      }
      updateHMI0();*/
      break;
    case Therapy1:
      updateHMI1();
      therapy1();
      currentState = Start;
      break;
    case Therapy2:
      int level = selectLevel();
      updateHMI2();
      therapy2(level);
      currentState = Start;
      break;
  }
}

int readFlexSensor() {
  int ADC = analogRead(flexSensor);
  int V = ADC * (3.3 / 4095.0);
  int flex = (V - 1.9947) / 0.0078; // Flex angle in degrees
  return flex;
}

int readPressureSensor() {
  int ADC = analogRead(pressureSensor);
  int V = ADC * (3.3 / 4095.0);
  int pressure = (V - 0.46) / 0.0086; // Pressure in kPa
  return pressure;
}

// Function definitions
void updateHMI0() {
  // Send therapy time data to the HMI
  Serial2.write('n'); Serial2.write('0'); Serial2.write('.'); Serial2.write('v'); Serial2.write('a'); Serial2.write('l'); Serial2.write('=');
  Serial2.print(therapyTime); Serial2.write(0xFF); Serial2.write(0xFF); Serial2.write(0xFF);
  delay(1000);
}

void updateHMI1() {

}

void updateHMI2() {

}

int readTherapyTime() {
  int i = 0; int act = 0;
  while(i < 7) {
    int act = Serial2.read();
    if(act == -1)
      continue;
    data[i] = act;
    i++;
  }
  if(data[1] == 0 && data[2] == 3) // data[1]: page, data[2]: component, data[3]: value
    return data[3];
}

int readTherapy() {
  int i = 0; int act = 0;
  while(i < 7) {
    int act = Serial2.read();
    if(act == -1)
      continue;
    data[i] = act;
    i++;
  }
  if(data[1] == 0 && data[2] == 4) // data[1]: page, data[2]: component
    return 1;
  return 0;
}

void therapy1() {
  int currentTime = therapyTime;
  while(currentTime >= 0){ // Debugging ############################
    Serial.println("Therapy 1: " + String(currentTime / 60000.0) + " minutes left");
    ledcWrite(Motor1, 4095); delay(10 * 1000); Serial.println(readFlexSensor());
    ledcWrite(Motor1, 0); delay(5 * 1000);
    ledcWrite(Motor2, 4095); delay(10 * 1000); Serial.println(readFlexSensor());
    ledcWrite(Motor2, 0); delay(5 * 1000);
    currentTime -= 30000;
    buzzerMelody(1);
  }
  buzzerMelody(0);
}

void therapy2(int level) {
  int pressureLevel = 0;
  if(level == 1) {
    pressureLevel = lowPressure + 50;
    while(readPressureSensor() < lowPressure)
      ledcWrite(Motor1, 4095);
  } else if(level == 2) {
    pressureLevel = mediumPressure + 50;
    while(readPressureSensor() < mediumPressure)
      ledcWrite(Motor1, 4095);
  } else if(level == 3) {
    pressureLevel = highPressure + 50;
    while(readPressureSensor() < highPressure)
      ledcWrite(Motor1, 4095);
  }
  ledcWrite(Motor1, 0);

  int currentTime = therapyTime;
  while(currentTime >= 0){ // Debugging ############################
    Serial.println("Therapy 2: " + String(currentTime / 60000.0) + " minutes left"); 
    Serial.println("Pressure: " + String(readPressureSensor())); 
    Serial.println("Flex: " + String(readFlexSensor()));
    if(readPressureSensor() > pressureLevel) 
      buzzerMelody(1);
    delay(1000);
    currentTime -= 1000;
  }
  buzzerMelody(0);
}

int selectLevel() {
  Serial.println("Select level: 1, 2 or 3"); // Debugging ############################
  while(Serial.available() == 0); // Debugging ############################
  if(Serial.available() > 0) { // Debugging ############################
    char c = Serial.read();
    if(c == '1') {
      return 1;
    } else if(c == '2') {
      return 2;
    } else if(c == '3') {
      return 3;
    }
  }
}

void buzzerMelody(int melody) {
  switch (melody) {
    case 0: // Melody 1: Super Mario Bros theme
      int melody[] = {
        NOTE_E5, NOTE_E5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_G4
      };
      int noteDurations[] = {
        8, 4, 4, 8, 4, 2, 2
      };
      int size = sizeof(noteDurations) / sizeof(int); // Get the size of the array 
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(buzzer, melody[thisNote], noteDuration); // Play the tone (Square wave at the given frequency: the tone)
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzzer); // Stop the tone playing
      }
      break;
    case 1: // Melody 2: Counting tone
      int melody[] = {
        NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
      };
      int noteDurations[] = {
        4, 4, 4, 4, 4, 4, 4, 4
      };
      int size = sizeof(noteDurations) / sizeof(int); // Get the size of the array 
      for (int thisNote = 0; thisNote < size; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(buzzer, melody[thisNote], noteDuration); // Play the tone (Square wave at the given frequency: the tone)
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzzer); // Stop the tone playing
      }
      break;
    default:
      break;
  }
}