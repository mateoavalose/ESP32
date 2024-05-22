#include <Arduino.h>
#include "pitches.h"

/*
 Sensors
*/
const int pressureSensor = 27;
const int flexSensor = 26;

/*
 Actuators
*/
const int buzzer = 25;
const int Motor1 = 33;
const int Motor2 = 32;

/*
  Variables
*/
// Data received from the HMI
int HMI_Data [7]; // 0: Start, 1: Page, 2: Component, 3: Event, 4: Empty, 5: Empty, 6: Empty
// Therapy states
enum State {Start, Therapy1, Therapy2};
State currentState = Start;
// Base therapy time in milliseconds (10 minutes)
int therapyTime = 600000;
// Pressure levels in kPa and range
const int lowPressure = 2;
const int mediumPressure = 4;
const int highPressure = 6;
const int range = 2;
// Selected therapy level
int level = 1;

/*
  Function declarations
*/
void updateHMI_int(String identifier, int value);
void updateHMI_txt(String identifier, String text);
void readHMI();
int readFlexSensor();
int readPressureSensor();
void therapy1();
void therapy2();
void buzzerMelody(int melody);

/*
  Setup and loop
*/
void setup() {
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
      updateHMI_int("n0", round(therapyTime / 60000.0));
      if(Serial2.available() > 0) {
        readHMI();
        if(HMI_Data[1] == 0 && HMI_Data[2] == 3)
          therapyTime += 60000;
        else if(HMI_Data[1] == 0 && HMI_Data[2] == 4)
          therapyTime -= 60000;
        else if(HMI_Data[1] == 0 && HMI_Data[2] == 5)
          currentState = Therapy1;
        else if(HMI_Data[1] == 0 && HMI_Data[2] == 6)
          currentState = Therapy2;
      }
      break;
    case Therapy1:
      updateHMI_int("n0", round(therapyTime / 60000.0));
      updateHMI_int("n1", readFlexSensor());
      updateHMI_int("n2", readPressureSensor());
      if(Serial2.available() > 0) {
        readHMI();
        if(HMI_Data[1] == 1 && HMI_Data[2] == 3) {
          therapy1();
          currentState = Start;
        } else if(HMI_Data[1] == 1 && HMI_Data[2] == 4)
          currentState = Start; 
      }
      break;
    case Therapy2:
      updateHMI_int("n0", round(therapyTime / 60000.0));
      updateHMI_int("n1", readFlexSensor());
      updateHMI_int("n2", readPressureSensor());
      updateHMI_int("n3", level);
      if(Serial2.available() > 0) {
        readHMI();
        if(HMI_Data[1] == 2 && HMI_Data[2] == 3) {
          level = 1; 
          updateHMI_int("n3", level);
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 4) {
          level = 2; 
          updateHMI_int("n3", level);
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 5) {
          level = 3; 
          updateHMI_int("n3", level);
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 6) {
          therapy2();
          currentState = Start;
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 6)
          currentState = Start;
      }
      break;
  }
}

/*
  Function definitions
*/
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

void therapy1() {
  enum StateT1 {pressurize, depressurize, hold, pause};
  StateT1 currentStateT1 = pressurize;
  StateT1 previousStateT1 = pressurize;
  const int onTime = 10000;
  const int offTime = 5000;
  int currentTime = millis();

  while(millis() - currentTime < therapyTime) {
    switch(currentStateT1) {
      case pressurize:
        ledcWrite(0, 4095);
        ledcWrite(1, 0);
        if(millis() - currentTime >= onTime) {
          previousStateT1 = pressurize;
          currentStateT1 = hold;
          currentTime = millis();
        }
        break;
      case depressurize:
        ledcWrite(0, 0);
        ledcWrite(1, 4095);
        if(millis() - currentTime >= onTime) {
          previousStateT1 = depressurize;
          currentStateT1 = hold;
          currentTime = millis();
        }
        break;
      case hold:
        ledcWrite(0, 0);
        ledcWrite(1, 0);
        if(millis() - currentTime >= offTime) {
          if(previousStateT1 == pressurize)
            currentStateT1 = depressurize;
          else if(previousStateT1 == depressurize) {
            currentStateT1 = pressurize;
            buzzerMelody(1);
          }
          currentTime = millis();
        }
        break;
      case pause:
        ledcWrite(0, 0);
        ledcWrite(1, 0);
        if(Serial2.available() > 0) {
          readHMI();
          if(HMI_Data[1] == 1 && HMI_Data[2] == 4) {
            currentStateT1 = depressurize;
            currentTime = millis();
          }
        }
        break;
    }
    updateHMI_int("n0", round(currentTime / 60000.0));
    updateHMI_int("n1", readFlexSensor());
    updateHMI_int("n2", readPressureSensor());
    if(Serial2.available() > 0) {
      readHMI();
      if(HMI_Data[1] == 1 && HMI_Data[2] == 4) {
        currentStateT1 = depressurize;
        delay(onTime);
        break;
      }
    }
    delay(500);
  }
  buzzerMelody(0);
}

void therapy2() {
  int pressureLevel = 0;
  if(level == 1) {
    pressureLevel = lowPressure + range;
    while(readPressureSensor() < lowPressure)
      ledcWrite(0, 4095);
  } else if(level == 2) {
    pressureLevel = mediumPressure + range;
    while(readPressureSensor() < mediumPressure)
      ledcWrite(0, 4095);
  } else if(level == 3) {
    pressureLevel = highPressure + range;
    while(readPressureSensor() < highPressure)
      ledcWrite(0, 4095);
  }
  ledcWrite(0, 0);

  int currentTime = millis();
  while(millis() - currentTime < therapyTime) {
    updateHMI_int("n0", round(currentTime / 60000.0));
    updateHMI_int("n1", readFlexSensor());
    updateHMI_int("n2", readPressureSensor());
    if(readPressureSensor() > pressureLevel) 
      buzzerMelody(1);
    else if(readPressureSensor() < pressureLevel - range) {
      while(readPressureSensor() < pressureLevel)
        ledcWrite(0, 4095);
      ledcWrite(0, 0);
    }
    if(Serial2.available() > 0)
      readHMI();
      if(HMI_Data[1] == 2 && HMI_Data[2] == 4)
        break;
    delay(500);
  }
  buzzerMelody(0);
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
        4, 2, 4, 1, 4, 2, 4, 4
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