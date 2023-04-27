#include "heartbeat.h"

const char* apiKey_heartbeat = "B0HP8Y8MUQIWP3T6";
unsigned long channel_id_hearbeat = 2123478;

void send_heartbeat(){

    ThingSpeak.writeField(channel_id_hearbeat, 1, 1, apiKey_heartbeat); //send heartbeat signal "1" to ThingSpeak
                                                                        //listened by Android App
}