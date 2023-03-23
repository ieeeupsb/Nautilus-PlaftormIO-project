#include "encoder.h"

Encoder::Encoder(int pinA, int pinB) {
    encPinA = pinA;
    encPinB = pinB;
}

Encoder::~Encoder() {
    detachInterrupt(encPinA);
}

void Encoder::setup() {
    pinMode(encPinA, INPUT);
    pinMode(encPinB, INPUT);
    this->zeroCount();
    attachInterruptArg(digitalPinToInterrupt(encPinA), interrupt, static_cast<void *>(this), RISING);
}

void IRAM_ATTR Encoder::interrupt(void * obj) {
    
    Encoder *obj1 = static_cast<Encoder *>(obj);
    if(digitalRead(obj1->encPinB) == HIGH){
        obj1->count--;
    }

    else
        obj1->count++;
}

void Encoder::zeroCount(){
    count = 0;
}

long Encoder::getCount() {   
    return count;
}