#include <Arduino.h>
#include "Adafruit_MotorShield.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>

#define ENCA_LEFT 23
#define ENCB_LEFT 5
#define ENCA_RIGHT 16
#define ENCB_RIGHT 17

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
Adafruit_DCMotor *motor_right = AFMS.getMotor(2);

volatile int leftEncCount = 0;
volatile int rightEncCount = 0;

const int ir1 = 39;
const int ir2 = 36;
const int ir3 = 34;
const int ir4 = 35;
const int ir5 = 32;
const int iman = 19;

void setupEncoders();
void leftISR();
void rightISR();

void setup()
{
  setupEncoders();
  AFMS.begin();
  Serial.begin(115200);

  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);
  pinMode(ir5,INPUT);
  pinMode(iman, OUTPUT);
}

void loop()
{

  digitalWrite(iman, LOW);

  Serial.print("Left Encoder Count: ");
  Serial.print(leftEncCount);
  Serial.print(" | Right Encoder Count: ");
  Serial.println(rightEncCount);

  delay(20);
}

// -------- //

//Encoder Interrupt Service Routines (ISRs)
//IRAM_ATTR makes sure that the code is stored in the internal RAM of the ESP32,
//which is way faster than the flash memory that the code usually resides in.

void IRAM_ATTR leftISR() {
  if (digitalRead(ENCB_LEFT)) {
    leftEncCount--;
  }
  else {
    leftEncCount++;
  }
}

void IRAM_ATTR rightISR() {
  if (digitalRead(ENCB_RIGHT)) {
    leftEncCount--;
  }
  else {
    leftEncCount++;
  }
}

void setupEncoders() {
  pinMode(ENCA_LEFT, INPUT);
  pinMode(ENCB_LEFT, INPUT);
  pinMode(ENCA_RIGHT, INPUT);
  pinMode(ENCB_RIGHT, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA_LEFT), leftISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_RIGHT), rightISR, RISING);
}
