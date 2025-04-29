#line 1 "c:\\Users\\wuni1\\OneDrive\\桌面\\code\\Arduino\\makeNTU2025\\makeNTU2025\\move.h"
#ifndef MOTOR_CONST
#define MOTOR_CONST
const int R_1A = 8; //digital pin
const int R_1B = 9; //PWM
const int L_1A = 8; //digital pin
const int L_1B = 9; //PWM

#endif

class move{
    void setPin();
    void forward(int dist);
    void backward(int dist);
    void turn_left(int angle);
    void turn_right(int angle);
};