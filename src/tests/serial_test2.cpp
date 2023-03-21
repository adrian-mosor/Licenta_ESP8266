//ESP -> MEGA (using D4, which is GPIO2 Pin, used for TX)

#include <Arduino.h>
#include <SoftwareSerial.h>

String temp;
int stop = -1;
bool kill = false;

void setup(){
  
    Serial.begin(9600);
    Serial1.begin(9600);
    // Serial.println("ESP begin to transmit");
    // Serial.println("Sending message...");
    
    delay(1000);
    
    temp = String("ok");
    Serial1.println(temp);
    // Serial.println("Message sent!");

}


void loop()
{



}