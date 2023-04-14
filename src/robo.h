#include "Arduino.h"
#include "math.h"
#include "encoder.h"
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <PID_v1.h>

class robo{
    public:
        robo(); //constructor
        ~robo();
        float v1, v2;
        float dt_x;
        float dt_y;
        float dt_teta;
        float v_t, w_t, d_i, delta_teta_i;
        float f_x, f_y, f_teta;

        float v1_ref,v2_ref;
        void velocidade_1();
        void velocidade_2();
        void velocidade_linear();
        void velocidade_angular();
        void impulsos();
        void delta_teta();
        void posicao_delta_t();
        void posicao_x_t();
        void posicao_y_t();
        void odometry();
        
    private:
        Encoder left_encoder, right_encoder;
        Adafruit_MotorShield AFMS;
        PID *left_PID, *right_PID;
        float aliment, saida, target;
        const float dist_rodas = 0.14;
        const float imp_met = 0.0000532;
};
