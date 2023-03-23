#include <Arduino.h>
#include "Adafruit_MotorShield.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>
#include "encoder.h"

#define ENCA_LEFT 23
#define ENCB_LEFT 5
#define ENCA_RIGHT 16
#define ENCB_RIGHT 17

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
Adafruit_DCMotor *motor_right = AFMS.getMotor(2);

Encoder leftEncoder(ENCA_LEFT, ENCB_LEFT);

const int ir1 = 39;
const int ir2 = 36;
const int ir3 = 34;
const int ir4 = 35;
const int ir5 = 32;
const int iman = 19;

void setup()
{
  //setupEncoders();
  leftEncoder.setup();
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

  Serial.print("LEFT ENC: ");
  Serial.println(leftEncoder.getCount());
  digitalWrite(iman, LOW);

  delay(20);
}

// -------- //
