#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SPI.h>
#include "robo.h"

#define ENCA_LEFT 26
#define ENCB_LEFT 25
#define ENCA_RIGHT 16
#define ENCB_RIGHT 17

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
Adafruit_DCMotor *motor_right = AFMS.getMotor(2);

Encoder leftEncoder(ENCA_LEFT, ENCB_LEFT);
Encoder rightEncoder(ENCA_RIGHT, ENCB_RIGHT);
robo r;

const int ir1 = 34;
const int ir2 = 35;
const int ir3 = 34;
const int ir4 = 32;
const int ir5 = 15;
const int iman = 14;

int v_ir1, v_ir2, v_ir3, v_ir4, v_ir5;
float interval=0.040;
unsigned long last_cycle=0, now;


void setup()
{
  //setupEncoders();
  leftEncoder.setup();
  rightEncoder.setup();
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
  now = millis();
  if(now-last_cycle>interval){
    last_cycle+=interval;
  
    v_ir1 = analogRead(ir1);
    v_ir2 = analogRead(ir2);
    v_ir3 = analogRead(ir3);
    v_ir4 = analogRead(ir4);
    v_ir5 = analogRead(ir5);
    Serial.print("Sensor:");
    Serial.printf("%d %d %d %d %d\n", v_ir1, v_ir2, v_ir3, v_ir4, v_ir5);
    Serial.print(r.v1);
 
 // Serial.print("LEFT ENC: ");
 // Serial.println(leftEncoder.getCount());
 // Serial.print("RIGHT ENC: ");
 // Serial.println(rightEncoder.getCount());
  }
  delay(1000);
}

// -------- //
