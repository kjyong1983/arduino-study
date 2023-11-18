#include <Servo.h>
#include "pitches.h"

int ledPin = 3;
int servoPin = 9;
int analogPinA0 = A0;
int bzPin = 6;
int playTime = 50;

Servo servo;

void setup() {
  servo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  pinMode(bzPin, OUTPUT);
}

void loop() {

  int analogInput = analogRead(analogPinA0);
  // int hz = map(analogInput, 0, 1023, 20, 20000);
  // tone(bzPin, hz, 100);

  tone(bzPin, NOTE_C4, playTime);
  delay(100);
  tone(bzPin, NOTE_D4, playTime);
  delay(100);
  tone(bzPin, NOTE_E4, playTime);
  delay(100);
  tone(bzPin, NOTE_F4, playTime);
  delay(100);
  tone(bzPin, NOTE_G4, playTime);
  delay(100);
  tone(bzPin, NOTE_A4, playTime);
  delay(100);
  tone(bzPin, NOTE_B4, playTime);
  delay(100);
  tone(bzPin, NOTE_C5, playTime);
  delay(100);
}
