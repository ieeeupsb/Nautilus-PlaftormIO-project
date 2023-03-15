#include <Arduino.h>

#define CTIME 50 // micros

unsigned long t;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(micros() - t < CTIME) {
    t = micros();

  }
}