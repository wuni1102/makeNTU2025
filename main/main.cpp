#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "move.h"
#include "myhead.h"
#include "hands.h"
#include "screen.h"

const char* ssid = "Galaxy A71 5G1CBA";
const char* password = "zwfz2867";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

Move move(13, 14, 15, 16, 100, 3); // int R_1A, int R_1B, int L_1A, int L_1B, double DPS, double R
myHead head(17, 18, 19, 20, 100); // int IN_1, int IN_2, int IN_3, int IN_4, int DT(ms)
Hands hands(21, 22, 23, 25, 26, 27, 32, 33, 100);
    // int LIN_1, int LIN_2, int LIN_3, int LIN_4, int RIN_1, int RIN_2, int RIN_3, int RIN_4, int DT(ms)
Screen screen(4, 5, 12, 128, 64); // int RW, int E, int CS, int WIDTH, int HEIGHT

void setup(){

    Serial.begin(115200);
    
	// pinMode(5, OUTPUT);
    move.setPin(); // set pinMode for move's motor
    move.test(15); // cm, for debug
    head.setPin(); // set pinMode for head's motor
    head.test(); // for debug
    hands.setPin(); // set pinMode for hands' motor
    hands.test(); // for debug
    screen.setPin(); // u8g2.begin()
    screen.test(); // for debug
	
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop(){
    // Check WiFi connection status
    
    HTTPClient http;
    String serverPath = "http://192.168.180.230:5000/data?name=Hello"; //replace with server's IP address
    
    http.begin(serverPath); //GET request
    int httpCode = http.GET(); 

    if (httpCode > 0){ //If alright
        //TODO
        Serial.print("Content-Type = ");
        Serial.println(http.header("Content-Type"));

        String payload = http.getString();
        Serial.println("Received JSON:");
        Serial.println(payload);
    
        Serial.print("Content-Length = ");
        Serial.println(http.header("Content-Length"));

    }else{
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
    
    delay(5000);  //send request every 5s
    Serial.println("hello");
}