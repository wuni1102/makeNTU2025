#include "screen.h"

using namespace std;

void Screen::setPin(){
    u8g2.begin();
    u8g2.clearBuffer();
}

void Screen::print(String str){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_unifont_t_chinese2);
    int position_x = (WIDTH/2)-(str.length()/2);
    int position_y = (HEIGHT/2);
    u8g2.drawUTF8(position_x, position_y, str.c_str());
    u8g2.sendBuffer();
}

void Screen::set(String str, int pos){
    int position_x, position_y;
    switch(pos){
        case 1:
            position_x = 0;
            position_y = 0;
            break;
        case 2:
            position_x = (WIDTH/2)-(str.length()/2);
            position_y = 0;
            break;
        case 3:
            position_x = WIDTH-str.length();
            position_y = 0;
            break;
        case 4:
            position_x = 0;
            position_y = HEIGHT/2;
            break;
        case 5:
            position_x = (WIDTH/2)-(str.length()/2);
            position_y = HEIGHT/2;
            break;
        case 6:
            position_x = WIDTH-str.length();
            position_y = HEIGHT/2;
            break;
        case 7:
            position_x = 0;
            position_y = HEIGHT;
            break;
        case 8:
            position_x = (WIDTH/2)-(str.length()/2);
            position_y = HEIGHT;
            break;
        case 9:
            position_x = WIDTH-str.length();
            position_y = HEIGHT;
            break;
        default:
            Serial.println("Error: Screen::set");
    }
    u8g2.drawUTF8(position_x, position_y, str.c_str());
}

void Screen::send(){
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

void Screen::reset(){
    u8g2.clearBuffer();
}

void Screen::test(){
    print("哈囉世界!!!");
    set("菜單測試", 1);
    set("choices", 5);
    set("哈囉", 7);
    set("世界", 8);
    set("!!!", 9);
    send();
    reset();
    Serial.println("screen test finished");
}