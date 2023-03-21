//ESP receives from MEGA 

#include <Arduino.h>

String receivedMessage;

void setup() {

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    Serial.println();
    Serial.println("ESP8266 ready to receive. Please connect RX pin!");
    
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
}
void loop() { // run over and over

    if (Serial.available()) {   //example of printing on serial monitor directly 

        // Serial.write(Serial.read());

        receivedMessage = Serial.readString();
        Serial.println("Received message:");
        Serial.println(receivedMessage);

        
    }
}