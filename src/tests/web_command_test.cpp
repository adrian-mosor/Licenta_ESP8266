//Android (http request) -> ESP (server) -> Mega (RGB);

#include "wireless_conn.h"
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <ThingSpeak.h>

	
ESP8266WebServer server(80);    //80 is the default port for http
String message;
String temp;

void handleRootPath(){  //handler for the root path

    // server.send(200, "text/plain", "got the message dude"); //response to http request
    
    if (server.hasArg("plain")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }
 
    // String message = server.arg("plain") + "\n";
    String message = server.arg("plain");

    Serial.println("ESP8266 body received: ");
    Serial.println(message);
    Serial.println("------------------");

    if(message.equals("rgb_on_test")){  //received correct message from http request

        Serial1.println(message);
        server.send(200, "text/plain", "Got the message rgb_on_test");  //response back to the sender
    }else{
        
        server.send(200, "text/plain", "Wrong message to server");  //response back to the sender
    }

}


void setup(){
    
    Serial.begin(9600);
    Serial1.begin(9600);

    setup_Wifi();
    
    server.on("/", handleRootPath); //associate the handler function in order to respond to http request
    server.begin();
    Serial.println("Server listening");
}

void loop(){

    server.handleClient();  //handle the incoming requests
}