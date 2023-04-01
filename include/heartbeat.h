#pragma once

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

//set ThingSpeak credentials for heartbeat
extern const char* apiKey_heartbeat;
extern unsigned long channel_id_hearbeat;

void send_heartbeat();