#pragma once

#include <Arduino.h>
#include <EEPROM.h> //emulated flash memory as EEPROM

//addresses of EEPROM for data to be stored
#define ADRESS_CHANNEL_ID_1 0
#define ADRESS_CHANNEL_ID_2 10
#define ADRESS_CHANNEL_ID_3 20

#define ADRESS_APIKEY_1 40
#define ADRESS_APIKEY_2 60
#define ADRESS_APIKEY_3 80

#define MAX_APIKEY_LENGTH 16
#define MAX_CHANNELID_LENGTH 7

void store_credentials_EEPROM(const unsigned long channel_id_1, const unsigned long channel_id_2, const unsigned long channel_id_3, 
    const char* apiKey_1, const char* apiKey_2, const char* apiKey_3);

String get_APIKey_EEPROM(const int numberCase);
unsigned long get_channelID_EEPROM(const int numberCase);
