#include "hands.h"

void Hands::setPin(){
    left.setPin();
    right.setPin();
}

void Hands::raise_L(int angle){
    left.direction += angle;
    left.direction %= 360;
    left.forward(angle);
}
void Hands::raise_R(int angle){
    right.direction += angle;
    right.direction %= 360;
    right.forward(angle);
}

void preRaise(myHead &h){
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

void Hands::raise(char c){ // L, R, B : left, right, both
    switch(c){
        case 'L':
            preRaise(left);
            break;
        case 'R':
            preRaise(right);
            break;
        case 'B':
            preRaise(left);
            preRaise(right);
            break;
        default:
            Serial.println("error: Hands::raise");
            break;
    }
}

void Hands::putDown_L(int angle){
    left.direction -= angle;
    left.direction %= 360;
    left.backward(angle);
}
void Hands::putDown_R(int angle){
    right.direction -= angle;
    right.direction %= 360;
    right.backward(angle);
}

void prePutDown(myHead &h){
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

void Hands::putDown(char c){ // L, R, B : left, right, both
    switch(c){
        case 'L':
            prePutDown(left);
            break;
        case 'R':
            prePutDown(right);
            break;
        case 'B':
            prePutDown(left);
            prePutDown(right);
            break;
        default:
            Serial.println("error: Hands::putDown");
            break;
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
    Serial.println("hands test finished");
}