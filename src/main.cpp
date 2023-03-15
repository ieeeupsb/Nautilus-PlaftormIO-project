#include <Arduino.h>
#include "Adafruit_MotorShield.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
Adafruit_DCMotor *motor_right = AFMS.getMotor(2);

const int ir1 = 8;
const int ir2 = 9;
const int ir3 = 10;
const int ir4 = 11;
const int ir5 = 12;
const int iman = 6;
int a,b,c,d,e;


void setup()
{
  AFMS.begin();
  Serial.begin(9600);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);
  pinMode(ir5,INPUT);
  pinMode(iman, OUTPUT);
}

void loop()
{
  a=digitalRead(ir1);
  b=digitalRead(ir2);
  c=digitalRead(ir3);
  d=digitalRead(ir4);
  e=digitalRead(ir5);
  Serial.print("Sensor1: ");
  Serial.print(a);
  Serial.print("Sensor2: ");
  Serial.print(b);
  Serial.print("Sensor3: ");
  Serial.print(c);
  Serial.print("Sensor4: ");
  Serial.print(d);
  Serial.print("Sensor5: ");
  Serial.print(e);

  delay(10);
}