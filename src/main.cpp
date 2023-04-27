//Android (http request) -> ESP (server) -> Mega (RGB);

#include <Arduino.h>

#include "wireless_conn.h"
#include "receive_data.h"
#include "heartbeat.h"
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
    }else
    if (message.startsWith("thingspeak_sync")) {    //the format sent from AndroidApp would be thingspeak_sync/chID1/chID2/chID3/APIKey1/APIKey2/APIKey3
        
        //find the indices of the separators ("/")
        int index1 = message.indexOf("/");
        int index2 = message.indexOf("/", index1 + 1);
        int index3 = message.indexOf("/", index2 + 1);
        int index4 = message.indexOf("/", index3 + 1);
        int index5 = message.indexOf("/", index4 + 1);
        int index6 = message.indexOf("/", index5 + 1);
        int index7 = message.indexOf("/", index6 + 1);

        //extract the values between the separators
        String chID1 = message.substring(index1 + 1, index2);
        String chID2 = message.substring(index2 + 1, index3);
        String chID3 = message.substring(index3 + 1, index4);
        String apiKey1 = message.substring(index4 + 1, index5);
        String apiKey2 = message.substring(index5 + 1, index6);
        String apiKey3 = message.substring(index6 + 1, index7);

        //process the extracted values
        Serial.println("Received ThingSpeak credentials:");
        Serial.println("chID1: " + chID1);
        Serial.println("chID2: " + chID2);
        Serial.println("chID3: " + chID3);
        Serial.println("apiKey1: " + apiKey1);
        Serial.println("apiKey2: " + apiKey2);
        Serial.println("apiKey3: " + apiKey3);

        //reponseMessage debug:
        String responseMessage = "Got the thingspeak_sync message";
        responseMessage += "\nReceived ThingSpeak credentials:\n";
        responseMessage += "chID1: " + chID1 + "\n";
        responseMessage += "chID2: " + chID2 + "\n";
        responseMessage += "chID3: " + chID3 + "\n";
        responseMessage += "apiKey1: " + apiKey1 + "\n";
        responseMessage += "apiKey2: " + apiKey2 + "\n";
        responseMessage += "apiKey3: " + apiKey3;

        //process the extracted values
        store_credentials_EEPROM(chID1.toInt(), chID2.toInt(), chID3.toInt(), apiKey1.c_str(), apiKey2.c_str(), apiKey3.c_str());
        data_setup_to_sync();   //get proper values stored in EEPROM

        // Serial.println("---------------------------------------");
        // Serial.println(responseMessage);
        // Serial.println("[<>] [<>] [<>] [<>] [<>] [<>] [<>] [<>]");

        server.send(200, "text/plain", responseMessage);
        // server.send(200, "text/plain", responseMessage);
    }
    else{
        
        Serial.println("Wrong message to server");
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

    // STORE EEPROM (DO NOT ABUSE OF THIS!)
    // store_credentials_EEPROM(2123504, 2123505, 2123506, "2EC6VJW7CNBAFMSK", "K5VMZMJQWIG6M68X", "G7J02CAXBRYS1YZL");
    // Serial.println("Setup(): Stored default/admin ThingSpeak credentials.");

    data_setup_to_sync();
    
    server.on("/", handleRootPath); //associate the handler function in order to respond to http request
    server.begin();
    Serial.println("Production: ESP8266 Server listening...");

    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on - LED indicator that esp8266 is connected to the internet and is listening

}

void loop(){

    server.handleClient();  //handle the incoming requests (from Android)

    receive_data_and_sync(); //receive data from MEGA from sensors and send them to ThingSpeak

    send_heartbeat(); //send heartbeat listened by Android App   
}