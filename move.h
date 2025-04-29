#ifndef MOTOR_CONST
#define MOTOR_CONST


#endif

class Move{
    const int R_1A = 8;
    const int R_1B = 9;
    const int L_1A = 10;
    const int L_1B = 11;
    const double DPS = 5; //cm, distance per second
    const double R = 3; //cm, radiaus of rotation
public:
    void setPin();
    void forward(double dist);
    void backward(double dist);
    void turn_left(int angle);
    void turn_right(int angle);
};