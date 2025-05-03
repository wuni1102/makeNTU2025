#include "myHead.h"

void myHead::setPin(){
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
}

void myHead::forward(int angle){
    direction += angle;
    direction %= 360;
    int steps = 4096*angle/360;
    while(steps--){
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, HIGH);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        delay(DT);
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        delay(DT);
    }
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
}

void myHead::backward(int angle){
    direction -= angle;
    direction %= 360;
    int steps = 4096*angle/360;
    while(steps--){
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, HIGH);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(DT);
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        delay(DT);
    }
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
}

void myHead::reset(){
    if(direction >= 0){
        if(direction >= 180){
            forward(360-direction);
        }else{
            backward(direction);
        }
    }else{
        if(direction >= -180){
            forward(direction*(-1));
        }else{
            backward(360+direction);
        }
    }
    direction = 0;
}

void myHead::test(){
    forward(90);
    delay(300);
    backward(180);
    delay(300);
    forward(90);
    delay(300);
    forward(360);
    delay(300);
    backward(360);
    Serial.println("myHead test finished");
}