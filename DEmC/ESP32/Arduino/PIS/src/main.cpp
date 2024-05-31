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
const int Motor = 33;

/*
  Variables
*/
// Data received from the HMI
int HMI_Data [7]; // 0: Start, 1: Page, 2: Component, 3: Event, 4: Empty, 5: Empty, 6: Empty
// Therapy states
enum State {Start, Therapy1, Therapy2};
State currentState = Start;
// Base therapy time in milliseconds (10 minutes)k
int therapyTime = 600000;
// Pressure levels in kPa and range
const int lowPressure = 2;
const int mediumPressure = 4;
const int highPressure = 6;
const int range = 2;
// Selected therapy level
int level = 0;

/*
  Function declarations
*/
void updateHMI_int(String identifier, int value);
void updateHMI_float(String identifier, String number);
String floatToString(float num);
void updateHMI_txt(String identifier, String text);
void updateHMI_page(int page);
void readHMI();
int readFlexSensor();
float readPressureSensor();
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
  pinMode(Motor, OUTPUT);
  // HMI
  Serial2.begin(9600);
  delay(5000);
  updateHMI_page(0);
}

void loop() {
  switch(currentState) {
    case Start:
      updateHMI_int("n0", therapyTime / 60000.0);
      if(Serial2.available() > 0) {
        readHMI();
        if(HMI_Data[1] == 0 && HMI_Data[2] == 5)
          therapyTime += 60000;
        else if(HMI_Data[1] == 0 && HMI_Data[2] == 4)
          therapyTime -= 60000;
            if(therapyTime/60000 < 1)
              therapyTime = 60000;
        else if(HMI_Data[1] == 0 && HMI_Data[2] == 2) {
          currentState = Therapy1;
          updateHMI_page(1);
        }
        else if(HMI_Data[1] == 0 && HMI_Data[2] == 3) {
          currentState = Therapy2;
          updateHMI_page(2);
        }
      }
      break;
    case Therapy1:
      updateHMI_float("x1", floatToString(therapyTime / 60000.0));
      updateHMI_int("n1", readFlexSensor());
      updateHMI_float("x0", floatToString(readPressureSensor()));
      if(Serial2.available() > 0) {
        readHMI();
        if(HMI_Data[1] == 1 && HMI_Data[2] == 2) {
          therapy1();
          currentState = Start;
        } else if(HMI_Data[1] == 1 && HMI_Data[2] == 7) {
          currentState = Start;
          updateHMI_page(0);
        }
      }
      break;
    case Therapy2:
      updateHMI_float("x1", floatToString(therapyTime / 60000.0));
      updateHMI_int("n1", readFlexSensor());
      updateHMI_float("x0", floatToString(readPressureSensor()));
      updateHMI_int("n0", level);
      if(Serial2.available() > 0) {
        readHMI();
        if(HMI_Data[1] == 2 && HMI_Data[2] == 15) {
          level = 1; 
          updateHMI_int("n0", level);
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 16) {
          level = 2; 
          updateHMI_int("n0", level);
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 17) {
          level = 3; 
          updateHMI_int("n0", level);
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 3) {
          therapy2();
          currentState = Start;
        } else if(HMI_Data[1] == 2 && HMI_Data[2] == 11) {
          currentState = Start;
          updateHMI_page(0);
        }
      }
      break;
  }
  delay(100);
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

void updateHMI_float(String identifier, String number) {
  String command = identifier + ".val=" + number;
  Serial2.print(command);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  delay(100);
}

String floatToString(float value) {
  value = value * 100;
  int intValue = (int)value;
  String strValue = String(intValue);
  if(value < 10.0) {
    strValue = "0" + strValue;
  }
  return strValue;
}

void updateHMI_txt(String identifier, String text) {
  String command = identifier + ".txt=\"" + text + "\""; 
  Serial2.print(command);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  Serial2.write(0xFF);
  delay(100);
}

void updateHMI_page(int page) {
  String command = "page page" + String(page);
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
  if(flex < 0)
    flex = 0;
  return flex;
}

float readPressureSensor() {
  int ADC = analogRead(pressureSensor);
  int V = ADC * (3.3 / 4095.0);
  float pressure = (V/5.0 - 0.04) / 0.09; // Pressure in kPa - formula for 0-5V output, has to be adjusted for 0-3.3V
  if(pressure < 0)
    pressure = 0;
  else if(pressure >= 9.5)
    while(pressure > 9){
      digitalWrite(Motor, 0);
      buzzerMelody(1);
      delay(500);
      readPressureSensor();
    }
  return pressure;
}

void therapy1() {
  enum StateT1 {pressurize, hold, pause};
  StateT1 currentStateT1 = pressurize;
  const int onTime = 8000;
  const int offTime = 20000;
  int startTime = millis();
  int timeLeft = therapyTime;
  bool exit = false;
  while(timeLeft > 0 && !exit) {
    switch(currentStateT1) {
      case pressurize:
        digitalWrite(Motor, 1);
        if(millis() - startTime >= onTime) {
          currentStateT1 = hold;
          startTime = millis();
        }
        timeLeft -= 420;
        break;
      case hold:
        digitalWrite(Motor, 0);
        if(millis() - startTime >= offTime) {
          currentStateT1 = pressurize;
          buzzerMelody(1);
          startTime = millis();
        }
        timeLeft -= 420;
        break;
      case pause:
        digitalWrite(Motor, 0);
        if(Serial2.available() > 0) {
          readHMI(); // delay of 10
          if(HMI_Data[1] == 1 && HMI_Data[2] == 2) {
            therapyTime = timeLeft;
            startTime = millis();
            currentStateT1 = hold;
          } else if(HMI_Data[1] == 1 && HMI_Data[2] == 7) {
            exit = true;
          }
            
        }
        break;
    }
    updateHMI_float("x1", floatToString(timeLeft / 60000.0)); // delay of 100
    updateHMI_int("n1", readFlexSensor()); // delay of 100
    updateHMI_float("x0", floatToString(readPressureSensor())); // delay of 100
    if(Serial2.available() > 0) {
      readHMI();
      if(HMI_Data[1] == 1 && HMI_Data[2] == 3) {
        currentStateT1 = pause;
      }
    }
    delay(100);
  }
  buzzerMelody(0);
  digitalWrite(Motor, 0);
  updateHMI_page(0);
}

void therapy2() {
  int pressureLevel = 0;
  if(level == 1) {
    pressureLevel = lowPressure + range;
    while(readPressureSensor() < lowPressure)
      digitalWrite(Motor, 1);
  } else if(level == 2) {
    pressureLevel = mediumPressure + range;
    while(readPressureSensor() < mediumPressure)
      digitalWrite(Motor, 1);
  } else if(level == 3) {
    pressureLevel = highPressure + range;
    while(readPressureSensor() < highPressure)
      digitalWrite(Motor, 1);
  }
  digitalWrite(Motor, 0);
  enum StateT2 {active, pause};
  StateT2 currentStateT2 = active;
  int timeLeft = therapyTime; 
  bool exit = false;
  while(timeLeft > 0 && !exit) {
    switch(currentStateT2) {
      case active:
        if(readPressureSensor() > pressureLevel) 
          buzzerMelody(1);
        else if(readPressureSensor() < pressureLevel - range) {
          while(readPressureSensor() < pressureLevel - range)
            digitalWrite(Motor, 1);
          digitalWrite(Motor, 0);
        }
        timeLeft -= 420;
        if(Serial2.available() > 0) {
          readHMI(); // delay of 10
          if(HMI_Data[1] == 2 && HMI_Data[2] == 4)
            currentStateT2 = pause;
        }
        break; 
      case pause:
        if(Serial2.available() > 0) {
          readHMI(); 
          if(HMI_Data[1] == 2 && HMI_Data[2] == 3) {
            currentStateT2 = active;
          } else if(HMI_Data[1] == 2 && HMI_Data[2] == 11) {
            exit = true;
          }
            
        }
        break;
      }
    updateHMI_float("x1", floatToString(timeLeft / 60000.0)); // delay of 100
    updateHMI_int("n1", readFlexSensor()); // delay of 100
    updateHMI_float("x0", floatToString(readPressureSensor())); // delay of 100
    delay(100);
  }
  digitalWrite(Motor, 0);
  buzzerMelody(0);
  updateHMI_page(0);
}

void buzzerMelody(int melodyNum) {
  switch (melodyNum) {
    case 0: { // Melody 1: Super Mario Bros theme1
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
      } break;
    case 1: { // Melody 2: Counting tone
        int melody[] = {
          NOTE_C5, NOTE_C5, NOTE_G5
        };
        int noteDurations[] = {
          4, 2, 4
        };
        int size = sizeof(noteDurations) / sizeof(int); // Get the size of the array 
        for (int thisNote = 0; thisNote < size; thisNote++) {
          int noteDuration = 1000 / noteDurations[thisNote];
          tone(buzzer, melody[thisNote], noteDuration); // Play the tone (Square wave at the given frequency: the tone)
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          noTone(buzzer); // Stop the tone playing
        }
      } break;
    default:
      break;
  }
}