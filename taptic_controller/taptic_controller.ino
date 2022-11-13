#include "pitches.h"

// Constants
const int knockSensor = 0;
const int threshold = 5;
const int knockFadeTime = 50;     // milliseconds we allow a knock to fade before we listen for another one. (Debounce timer.)
const int timeout = 500;

// Startup sound
int startupNotes[] = {
  NOTE_C4, NOTE_C5, NOTE_G4, NOTE_F4, NOTE_C5, NOTE_C4, NOTE_G4, 0
};
int startupDurations[] = {
  4, 8, 2, 4, 4, 4, 1, 1
};


// Notification sound
int notificationNotes[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int notificationDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// Variables
int knockSensorValue = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  play(startupNotes, startupDurations);
}

void loop() {
  knockSensorValue = analogRead(knockSensor);
  if (threshold < knockSensorValue) {
       delay(knockFadeTime);
       listen();
  }

  if (Serial.available() > 0) {
    play(notificationNotes, notificationDurations);
    Serial.read();
  }
}

void listen() {
  int knockNumber=1;               // Counter
  int startTime=millis();          // Reference for when this knock started
  int now=millis();
  do {
    // Listen
    knockSensorValue = analogRead(knockSensor);
    if (threshold < knockSensorValue) {
       knockNumber++;
       delay(knockFadeTime);
    }
  
    now=millis();
   
  } while (now - startTime < timeout);

  Serial.println(knockNumber);
}

void play(int* melody, int* noteDurations) {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
