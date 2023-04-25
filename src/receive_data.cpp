#include "receive_data.h"

// TO-DO new feature:
unsigned long channel_id_1;
unsigned long channel_id_2;
unsigned long channel_id_3;

const char* apiKey_1;
const char* apiKey_2;
const char* apiKey_3;

String sApiKey_1;
String sApiKey_2;
String sApiKey_3;

void data_setup_to_sync(){

        //getting credentials from EEPROM (new feature):
        channel_id_1 = get_channelID_EEPROM(1);
        channel_id_2 = get_channelID_EEPROM(2);
        channel_id_3 = get_channelID_EEPROM(3);

        sApiKey_1 = get_APIKey_EEPROM(1);
        apiKey_1 = sApiKey_1.c_str(); //conversion from String to const char*

        sApiKey_2 = get_APIKey_EEPROM(2);
        apiKey_2 = sApiKey_2.c_str(); 

        sApiKey_3 = get_APIKey_EEPROM(3);
        apiKey_3 = sApiKey_3.c_str();

        EEPROM.end();

        Serial.println("[<>] Credentials read from ESP:");
        Serial.print("CHANNEL_ID_1: "); Serial.println(channel_id_1);
        Serial.print("SAPIKEY_1: "); Serial.println(sApiKey_1);
        Serial.print("APIKEY_1: "); Serial.println(apiKey_1);
        
        Serial.print("CHANNEL_ID_2: "); Serial.println(channel_id_2);
        Serial.print("SAPIKEY_2: "); Serial.println(sApiKey_2);
        Serial.print("APIKEY_2: "); Serial.println(apiKey_2);

        Serial.print("CHANNEL_ID_3: "); Serial.println(channel_id_3);
        Serial.print("SAPIKEY_3: "); Serial.println(sApiKey_3);
        Serial.print("APIKEY_3: "); Serial.println(apiKey_3);
        Serial.println("[<>] [<>] [<>] [<>] [<>] [<>] [<>] [<>]");

        Serial.println();
}

void receive_data_and_sync()
{ 
    // receive data from MEGA from sensors and send them to ThingSpeak
    // get data credentials from emulated EEPROM of ESP in order to send them on ThingSpeak

    if (Serial.available())
    { 
        String stemp = Serial.readString();

        // Serial.println("Received string: ");
        // Serial.println(stemp);

        StaticJsonDocument<200> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, stemp);
        if (error)
        {
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


        if(temperature){
            ThingSpeak.writeField(channel_id_1, 1, temperature, apiKey_1); // 2nd parameter - field
        }

        if(temperatureF){
            ThingSpeak.writeField(channel_id_2, 1, temperatureF, apiKey_2);
        }

        if(humidity){
            ThingSpeak.writeField(channel_id_3, 1, humidity, apiKey_3);
        }

        Serial.println("Successfully sent data to ThingSpeak!");
        Serial.println("-------------------------------------------------");
        Serial.println();
    }
}