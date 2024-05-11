#include <Arduino.h>
#include "pitches.h"

#define BUZZZER_PIN  18 // GPIO18 connected to piezo buzzer

// Melody
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_G4
};

// Note durations: 4 = quarter note, 8 = eighth note, etc. (1 second divided by the duration)
int noteDurations[] = {
  8, 4, 4, 8, 4, 2, 2
};

void setup() {
  int size = sizeof(noteDurations) / sizeof(int); // Get the size of the array 
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZZER_PIN, melody[thisNote], noteDuration); // Play the tone (Square wave at the given frequency: the tone)

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZZER_PIN); // Stop the tone playing
  }
}

void loop() {
}