#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Galaxy A71 5G1CBA";
const char* password = "zwfz2867";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup(){

	pinMode(10, OUTPUT);
	
    Serial.begin(115200);
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
    //Check WiFi connection status

    HTTPClient http;
    String serverPath = "http://192.168.59.65:5000/data?name=Hello"; //replace with server's IP address

    http.begin(serverPath); //GET request
    int httpCode = http.GET(); 

    if (httpCode > 0){ //If alright
        //TODO
        Serial.print("Content-Type = ");
        Serial.println(http.header("Content-Type"));
    
        Serial.print("Content-Length = ");
        Serial.println(http.header("Content-Length"));

    }else{
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
    
    delay(5000);  //send request every 5s

}