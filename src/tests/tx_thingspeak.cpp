//MEGA -> ESP -> ThingSpeak

#include "wireless_conn.h"
#include <Arduino.h>
#include <ThingSpeak.h>
#include <ArduinoJson.h>

String receivedMessage;
const char* apiKey = "486R5S7M0349NF3V";
unsigned long channel_id = 2039388;

WiFiClient client;

void setup()
{
    // Setup serial port
    Serial.begin(9600);
    
    //connect to wi-fi
    setup_Wifi();

    ThingSpeak.begin(client);
    Serial.println("ThingSpeak succesfully started!");
}


void loop()
{
    // put your main code here, to run repeatedly:
    if (Serial.available()) {   //example of printing on serial monitor by a variable

        // float temp = atof(Serial.readString().c_str());
        String stemp = Serial.readString();

        // Serial.println("Received float:");
        // Serial.println(temp);

        Serial.println("Received string: ");
        Serial.println(stemp);

        StaticJsonDocument<200> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, stemp);
        if (error) {
          Serial.println("Failed to parse JSON data");
          return;
        }

        float temperature = jsonDoc["TemperatureC: "];

        Serial.println("Decoded temperature:");
        Serial.println(temperature);

        // ThingSpeak.writeField(channel_id, 2, temperature, apiKey); //2nd parameter - field
    }
}