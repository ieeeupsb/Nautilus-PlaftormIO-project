#include "robo.h"

//void robo::

robo::robo(){
    this->left_encoder = new Encoder();
    left_PID = new PID(&v1,);
    right_PID = new PID();
}

robo::~robo(){
}

void robo::velocidade_linear(){
    v_t = (v1 + v2) / 2 ;
}

void robo::velocidade_angular(){
    w_t = (v1-v2)/dist_rodas;
}

void robo::impulsos(){
    d_i = (left_encoder.getCount() + right_encoder.getCount())/2;
}

void robo::delta_teta(){
    delta_teta_i= (left_encoder.getCount() - right_encoder.getCount())/dist_rodas;
}

void robo::posicao_delta_t(){
    dt_teta = w_t;
}

void robo::posicao_x_t(){
    dt_x = v_t * cos(dt_teta);
}

void robo::posicao_y_t(){
    dt_y = v_t * sin(dt_teta);
}

void robo::odometry(){ 
    f_x = dt_x + (d_i * cos(dt_teta + (delta_teta_i / 2)));

    f_y = dt_y + (d_i*cos(dt_teta + (delta_teta_i/2)));

    f_teta = dt_teta + delta_teta_i;

}

void robo::velocidade_1(){
    v1=imp_met*left_encoder.getCount()/0.04 ;
}
void robo::velocidade_2(){
    v2=imp_met*right_encoder.getCount()/0.04 ;  
}


