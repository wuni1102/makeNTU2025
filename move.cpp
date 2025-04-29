#include "move.h"
#include <cmath>

void Move::setPin(){
    pinMode(R_1A, OUTPUT);
    pinMode(R_1B, OUTPUT);
    pinMode(L_1A, OUTPUT);
    pinMode(L_1B, OUTPUT);
    digitalWrite(R_1A, LOW);
    digitalWrite(R_1B, LOW);
    digitalWrite(L_1A, LOW);
    digitalWrite(L_1B, LOW);
}

void Move::forward(double dist){
    double time = dist/DPS;
    digitalWrite(R_1A, HIGH);
    digitalWrite(R_1B, LOW);
    digitalWrite(L_1A, HIGH);
    digitalWrite(L_1B, LOW);
    delay(time*1000);
    digitalWrite(R_1A, LOW);
    digitalWrite(R_1B, LOW);
    digitalWrite(L_1A, LOW);
    digitalWrite(L_1B, LOW);
}

void Move::backward(double dist){
    double time = dist/DPS;
    digitalWrite(R_1A, LOW);
    digitalWrite(R_1B, HIGH);
    digitalWrite(L_1A, LOW);
    digitalWrite(L_1B, HIGH);
    delay(time*1000);
    digitalWrite(R_1A, LOW);
    digitalWrite(R_1B, LOW);
    digitalWrite(L_1A, LOW);
    digitalWrite(L_1B, LOW);
}

void Move::turn_left(int angle){
    double n_angle = angle/360*M_PI;
    double time = R*n_angle/DPS;
    digitalWrite(R_1A, HIGH);
    digitalWrite(R_1B, LOW);
    digitalWrite(L_1A, LOW);
    digitalWrite(L_1B, HIGH);
    delay(time*1000);
    digitalWrite(R_1A, LOW);
    digitalWrite(R_1B, LOW);
    digitalWrite(L_1A, LOW);
    digitalWrite(L_1B, LOW);
}

void Move::turn_right(int angle){
    double n_angle = angle/360*M_PI;
    double time = R*n_angle/DPS;
    digitalWrite(R_1A, LOW);
    digitalWrite(R_1B, HIGH);
    digitalWrite(L_1A, HIGH);
    digitalWrite(L_1B, LOW);
    delay(time*1000);
    digitalWrite(R_1A, LOW);
    digitalWrite(R_1B, LOW);
    digitalWrite(L_1A, LOW);
    digitalWrite(L_1B, LOW);
}

void Move::test(int m){
    const int m = 10;
    forward(m);
    turn_right(90);
    forward(m);
    turn_left(90);
    backward(m);
    turn_left(90);
    forward(2*m);
    backward(m);
    turn_right(450);
}