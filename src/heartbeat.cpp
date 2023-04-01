#include "heartbeat.h"

const char* apiKey_heartbeat = "4F94OIT6QBHHTRRB";
unsigned long channel_id_hearbeat = 2074976;

void send_heartbeat(){

    ThingSpeak.writeField(channel_id_hearbeat, 1, 1, apiKey_heartbeat); //send heartbeat signal "1" to ThingSpeak
                                                                        //listened by Android App
}