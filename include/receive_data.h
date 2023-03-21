#pragma once

#include <ThingSpeak.h>


//temperatureC
extern const char* apiKey_1;
extern unsigned long channel_id_1;
 
//temperatureF
extern const char* apiKey_2;
extern unsigned long channel_id_2;

//humidity
extern const char* apiKey_3;
extern unsigned long channel_id_3;

void receive_data_and_sync();