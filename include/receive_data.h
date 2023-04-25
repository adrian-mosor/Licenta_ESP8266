#pragma once

#include <ThingSpeak.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "thingspeak_credentials.h"

extern unsigned long channel_id_1;
extern unsigned long channel_id_2;
extern unsigned long channel_id_3;

extern const char* apiKey_1;
extern const char* apiKey_2;
extern const char* apiKey_3;

void data_setup_to_sync();

void receive_data_and_sync();
