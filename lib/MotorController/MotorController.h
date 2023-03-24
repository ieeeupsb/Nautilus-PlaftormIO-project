#pragma once
#include <Arduino.h>
#include "PID_v1.h"
#include "encoder.h"
#include <Adafruit_MotorShield.h>

class MotorController {
    public:
        MotorController(); // Constructor - Needs parameters
        ~MotorController(); // Destructor
        //What does the controller need to be able to do?
    private:
        //What data do we need to keep track of?

        // Object pointers:
        PID *leftPID, *rightPID;
        Encoder *leftEncoder, *rightEncoder;
        Adafruit_MotorShield *motorShield;
};