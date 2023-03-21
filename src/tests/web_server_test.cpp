// HTTP Post request -> Server

#include "wireless_conn.h"
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <ThingSpeak.h>

	
ESP8266WebServer server(80);    //80 is the default port for http

void handleRootPath(){  //handler for the root path

    // server.send(200, "text/plain", "got the message dude"); //response to http request
    
    if (server.hasArg("plain")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }
 
      String message = server.arg("plain") + "\n";
 
      Serial.println("ESP8266 body received: ");
      Serial.println(message);

      server.send(200, "text/plain", "Got the message");  //response back to the sender with the same message
}


void setup(){
    
    Serial.begin(9600);
    
    setup_Wifi();
    
    server.on("/", handleRootPath); //associate the handler function in order to respond to http request
    server.begin();
    Serial.println("Server listening");
}

void loop(){

    server.handleClient();  //handle the incoming requests

    
}