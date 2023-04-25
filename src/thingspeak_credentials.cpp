#include "thingspeak_credentials.h"

//adapter executed when getting credentials from Android App
void store_credentials_EEPROM (const unsigned long channel_id_1, const unsigned long channel_id_2, const unsigned long channel_id_3, 
    const char* apiKey_1, const char* apiKey_2, const char* apiKey_3)
{
    //do NOT abuse of this feature as EEPROM/flash-memory has limited write/erase cycles!

    EEPROM.begin(256);  //allocate a buffer in RAM of 256 bytes
    
    for (size_t i = 0; i < MAX_APIKEY_LENGTH; ++i) {
    
        EEPROM.write(ADRESS_APIKEY_1 + i, apiKey_1[i]);
        EEPROM.write(ADRESS_APIKEY_2 + i, apiKey_2[i]);
        EEPROM.write(ADRESS_APIKEY_3 + i, apiKey_3[i]);
    }
    
    EEPROM.put(ADRESS_CHANNEL_ID_1, String(channel_id_1).substring(0, MAX_CHANNELID_LENGTH));
    EEPROM.put(ADRESS_CHANNEL_ID_2, String(channel_id_2).substring(0, MAX_CHANNELID_LENGTH));
    EEPROM.put(ADRESS_CHANNEL_ID_3, String(channel_id_3).substring(0, MAX_CHANNELID_LENGTH));

    EEPROM.commit(); //one cycle of writing commiting all 3 channels to minimize wear on EEPROM/flash-memory
                    //executed only if data is different      

    EEPROM.end();   //release the RAM buffer 
}


unsigned long get_channelID_EEPROM(const int numberCase){

    EEPROM.begin(256); //allocate a buffer in RAM of 256 bytes
    char channelIDStr[MAX_CHANNELID_LENGTH + 1];
    unsigned long channelID;

    switch(numberCase){

        case 1:
            EEPROM.get(ADRESS_CHANNEL_ID_1, channelIDStr);
            EEPROM.end();
            channelIDStr[MAX_CHANNELID_LENGTH] = '\0'; // Ensure the string is null-terminated
            channelID = strtoul(channelIDStr, NULL, 10); // Convert the string to an unsigned long

            // Serial.print("[<>] Getting from ESP channelID temperatureC: ");
            // Serial.println(channelID);

            return channelID;

        case 2:
            EEPROM.get(ADRESS_CHANNEL_ID_2, channelIDStr);
            EEPROM.end();
            channelIDStr[MAX_CHANNELID_LENGTH] = '\0'; // Ensure the string is null-terminated
            channelID = strtoul(channelIDStr, NULL, 10); // Convert the string to an unsigned long

            // Serial.print("[<>] Getting from ESP channelID temperatureF: ");
            // Serial.println(channelID);

            return channelID;
            
        case 3:
            EEPROM.get(ADRESS_CHANNEL_ID_3, channelIDStr);
            EEPROM.end();
            channelIDStr[MAX_CHANNELID_LENGTH] = '\0'; // Ensure the string is null-terminated
            channelID = strtoul(channelIDStr, NULL, 10); // Convert the string to an unsigned long

            // Serial.print("[<>] Getting from ESP channelID humidity: ");
            // Serial.println(channelID);

            return channelID;

        default:
            Serial.println("[<>] ERROR: Unmatched case of reading int from ESP!");
            return -1; //error code
    }

}


String get_APIKey_EEPROM(const int numberCase){

    EEPROM.begin(256); //allocate a buffer in RAM of 256 bytes
    char apiKeyStr[MAX_APIKEY_LENGTH + 1];
    String APIKey;

    switch(numberCase){

        case 1:
            EEPROM.get(ADRESS_APIKEY_1, apiKeyStr);
            EEPROM.end(); //release the RAM buffer
            apiKeyStr[MAX_APIKEY_LENGTH] = '\0'; // Ensure the string is null-terminated

            APIKey = String(apiKeyStr);

            
            Serial.println("---EEPROM DEBUG GET---");
            Serial.println(apiKeyStr);
            Serial.println(APIKey);
            Serial.println("---EEPROM DEBUG GET---");

            // Serial.print("[<>] Getting from ESP APIKey temperatureC: ");
            // Serial.println(APIKey);
            
            return APIKey;

        case 2:
            EEPROM.get(ADRESS_APIKEY_2, apiKeyStr);
            EEPROM.end(); //release the RAM buffer
            apiKeyStr[MAX_APIKEY_LENGTH] = '\0'; // Ensure the string is null-terminated
            
            APIKey = String(apiKeyStr);

            // Serial.print("[<>] Getting from ESP APIKey temperatureF: ");
            // Serial.println(APIKey);

            return APIKey;
            
        case 3:
            EEPROM.get(ADRESS_APIKEY_3, apiKeyStr);
            EEPROM.end(); //release the RAM buffer
            apiKeyStr[MAX_APIKEY_LENGTH] = '\0'; // Ensure the string is null-terminated
            
            APIKey = String(apiKeyStr);
            
            // Serial.print("[<>] Getting from ESP APIKey temperatureF: ");
            // Serial.println(APIKey);

            return APIKey;

        default:
            Serial.println("[<>] ERROR: Unmatched case of reading String from ESP!");
            return "-1"; //error code 
    }

}
