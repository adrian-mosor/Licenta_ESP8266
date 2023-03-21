//Android (http request) -> ESP (server) -> Mega (RGB);

#include <Arduino.h>

#include "wireless_conn.h"
#include "receive_data.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);    //80 is the default port for http
String message;
String temp;
WiFiClient client;

void handleRootPath(){  //handler for the root path, triggered from server.handleClient();

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

    if(message.equals("rgb_hi")){  //received correct message from http request

        Serial1.println(message);
        server.send(200, "text/plain", "Got the message rgb_hi");  //response back to the sender
    }else
    if(message.equals("rgb_reset")){

        Serial1.println(message);
        server.send(200, "text/plain", "Got the message rgb_reset");  //response back to the sender
    }
    else{
        
        server.send(200, "text/plain", "ESP8266: Wrong message to server");  //response back to the sender
    }

}


void setup(){

    pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off
    
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial.println();
    Serial.println();
    
    setup_Wifi();

    ThingSpeak.begin(client);
    Serial.println("ThingSpeak succesfully started!");
    
    server.on("/", handleRootPath); //associate the handler function in order to respond to http request
    server.begin();
    Serial.println("Production: ESP8266 Server listening");

    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on - LED indicator that esp8266 is connected to the internet and is listening

}

void loop(){

    server.handleClient();  //handle the incoming requests (from Android)

    receive_data_and_sync(); //receive data from MEGA from sensors and send them to ThingSpeak
    
}