#include <Arduino.h>
#include <U8g2lib.h>

/*
wiring:
VSS=>GND
VDD=>5V
RS=>GND
R/W=>D9
E=>D3
PSB=>GND
BLA=>3.3V
BLK=>GND
CS=>D10 (have to connect to gnd of esp32)
*/

class Screen{
    const int CS;
    const int RW;
    const int E;

    const int WIDTH;
    const int HEIGHT;

    U8G2_ST7920_128X64_F_SW_SPI u8g2; // isTurned, SCK(RW), MOSI(E), CS(CS)
public:
    Screen(int RW, int E, int CS, int WIDTH, int HEIGHT):
        RW(RW), E(E), CS(CS), WIDTH(WIDTH), HEIGHT(HEIGHT), u8g2(U8G2_R0, RW, E, CS) {}
    void setPin();
    void print(String str);
    void set(String str, int pos); // content, 1~9 nine-grid
    void send();
    void reset();
    void test();
};