#include "pitches.h"

#define BUZZER_PIN 3
#define Bb3_PIN 4
#define D4_PIN 5
#define F4_PIN 6

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(Bb3_PIN, INPUT_PULLUP);
  pinMode(D4_PIN, INPUT_PULLUP);
  pinMode(F4_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  // read values from buttons
  int bb3 = digitalRead(Bb3_PIN);
  int d4 = digitalRead(D4_PIN);
  int f4 = digitalRead(F4_PIN);

  if (bb3 == HIGH){
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int note_duration = 1000 / 16;
    buzz(NOTE_AS3, note_duration);
  }
  if (d4 == HIGH){
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int note_duration = 1000 / 16;
    buzz(NOTE_D4, note_duration);
  }
  if (f4 == HIGH){
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int note_duration = 1000 / 16;
    buzz(NOTE_F4, note_duration);
  }

}

// basic function for making the buzzer play a note
void buzz(long frequency, long length) {

  // blink led
  digitalWrite(13, HIGH);
  
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(BUZZER_PIN, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(BUZZER_PIN, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);
 
}
