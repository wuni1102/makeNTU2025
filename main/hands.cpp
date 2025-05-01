#include "hands.h"

void Hands::setPin(){
    left.setPin();
    right.setPin();
}

void Hands::raise_L(int angle = 180){
    left.direction += angle;
    left.direction %= 360;
    left.forward(angle);
}
void Hands::raise_R(int angle = 180){
    right.direction += angle;
    right.direction %= 360;
    right.forward(angle);
}

void preRaise(Head &h){
    if(h.direction >= 0){
        if(h.direction >= 180){
            h.backward(h.direction-180);
        }else{
            h.forward(180-h.direction);
        }
    }else{
        if(h.direction >= -180){
            h.backward(180-h.direction*(-1));
        }else{
            h.forward(h.direction*(-1)-180);
        }
    }
    h.direction = 180;
}

void Hands::raise(char c = 'B'){ // L, R, B : left, right, both
    switch(c){
        case 'L':
            preRaise(left);
        case 'R':
            preRaise(right);
        case 'B':
            preRaise(left);
            preRaise(right);
        default:
            Serial.println("error: Hands::raise");
    }
}

void Hands::putDown_L(int angle = 180){
    left.direction -= angle;
    left.direction %= 360;
    left.backward(angle);
}
void Hands::putDown_R(int angle = 180){
    right.direction -= angle;
    right.direction %= 360;
    right.backward(angle);
}

void prePutDown(Head &h){
    if(h.direction >= 0){
        if(h.direction >= 180){
            h.forward(360-h.direction);
        }else{
            h.backward(h.direction);
        }
    }else{
        if(h.direction >= -180){
            h.forward(h.direction*(-1));
        }else{
            h.backward(360-h.direction*(-1));
        }
    }
    h.direction = 0;
}

void Hands::putDown(char c = 'B'){ // L, R, B : left, right, both
    switch(c){
        case 'L':
            prePutDown(left);
        case 'R':
            prePutDown(right);
        case 'B':
            prePutDown(left);
            prePutDown(right);
        default:
            Serial.println("error: Hands::putDown");
    }
}

void Hands::test(){
    raise();
    putDown('L');
    raise_R(150);
    putDown_L(90);
    raise_L(180);
    reset();
    raise('B');
    putDown('B');
}