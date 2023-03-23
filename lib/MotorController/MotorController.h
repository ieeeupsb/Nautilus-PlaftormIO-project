#pragma once
#include <Arduino.h>
#include "PID_v1.h"
#include "encoder.h"

class MotorController {
    public:
        MotorController();
        ~MotorController();
        //What does the controller need to be able to do?
    private:
        //What data do we need to keep track of?

        PID *leftPID, *rightPID;
        Encoder *leftEncoder, *rightEncoder;
};