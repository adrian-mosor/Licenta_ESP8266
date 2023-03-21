#include "receive_data.h"

#include <Arduino.h>
#include <ArduinoJson.h>

String receivedMessage;

//credentials for ThingSpeak

//temperatureC
const char* apiKey_1 = "486R5S7M0349NF3V";    
unsigned long channel_id_1 = 2039388;

//temperatureF
const char* apiKey_2 = "NVON0G6E6POWKGRP";    
unsigned long channel_id_2 = 2071204;

//humidity
const char* apiKey_3 = "1ZCLKDX2REMRH31O";
unsigned long channel_id_3 = 2071205;

void receive_data_and_sync(){   //receive data from MEGA from sensors and send them to ThingSpeak

    if (Serial.available()) {   //example of printing on serial monitor by a variable

        String stemp = Serial.readString();

        // Serial.println("Received string: ");
        // Serial.println(stemp);

        StaticJsonDocument<200> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, stemp);
        if (error) {
          Serial.println("Failed to parse JSON data");
          return;
        }

        float temperature = jsonDoc["TemperatureC: "];
        float temperatureF = jsonDoc["TemperatureF: "];
        float humidity = jsonDoc["Humidity: "];

        Serial.println("-------------Sending to ThingSpeak--------------");

        Serial.print("Decoded temperature to be sent: ");
        Serial.println(temperature);

        Serial.print("Decoded temperatureF to be sent: ");
        Serial.println(temperatureF);

        Serial.print("Decoded humidity to be sent: ");
        Serial.println(humidity);
        Serial.println();

        ThingSpeak.writeField(channel_id_1, 1, temperature, apiKey_1); //2nd parameter - field
        ThingSpeak.writeField(channel_id_2, 1, temperatureF, apiKey_2);
        ThingSpeak.writeField(channel_id_3, 1, humidity, apiKey_3);
        
        Serial.println("Successfully sent data to ThingSpeak!");
        Serial.println("-------------------------------------------------");
        Serial.println();

    }

}