#include "myhead.h"

class Hands{
    const int LIN_1, LIN_2, LIN_3, LIN_4;
    const int RIN_1, RIN_2, RIN_3, RIN_4;
    const int DT; // microseconds
    myHead left;
    myHead right;
public:
    Hands(int LIN_1, int LIN_2, int LIN_3, int LIN_4, int RIN_1, int RIN_2, int RIN_3, int RIN_4, int DT):
        left(LIN_1, LIN_2, LIN_3, LIN_4, DT),
        right(RIN_1, RIN_2, RIN_3, RIN_4, DT),
        LIN_1(LIN_1), LIN_2(LIN_2), LIN_3(LIN_3), LIN_4(LIN_4),
        RIN_1(RIN_1), RIN_2(RIN_2), RIN_3(RIN_3), RIN_4(RIN_4),
        DT(DT) {};
    void setPin();
    void raise_L(int angle = 180);
    void raise_R(int angle = 180);
    void raise(char c = 'B'); // L, R, B : left, right, both
    void putDown_L(int angle = 180);
    void putDown_R(int angle = 180);
    void putDown(char c = 'B'); // L, R, B : left, right, both
    void reset() {putDown();}
    void test();
};