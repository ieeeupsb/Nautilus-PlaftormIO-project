#include <Arduino.h>
// Voces podem adicionar cálculo de velocidade nessa biblioteca ou podem fazer mais pra frente.
class Encoder {
    public:
        Encoder(int pinA, int pinB);

        ~Encoder();

        void setup();

        //IRAM_ATTR makes sure that the code is stored in the internal RAM of the ESP32,
        //which is way faster than the flash memory that the code usually resides in.
        //This is important because an interrupt must be as fast as possible
        static void IRAM_ATTR interrupt(void * obj);

        void zeroCount();      // setter function, set a value to a specific Class variable
        
        long getCount();       // getter function, get a value to a specific Class variable

    private:
        volatile int count;
        int encPinA, encPinB;
        

};