#include <EEPROM.h>
#include <Arduino.h>

#define ADRESS_TEST 150
#define FIXED_SIZE 6    //qsid length

void writeEEPROM() {
    String qsid = "Global";

    Serial.println("writing eeprom ssid:");
    EEPROM.put(ADRESS_TEST, qsid);
    EEPROM.commit(); // Save the changes to EEPROM
    Serial.print("Wrote: ");
    Serial.println(qsid);
}

void readEEPROM() {
    Serial.println("Reading EEPROM ssid");
    String esid;

    EEPROM.get(ADRESS_TEST, esid);
    esid = esid.substring(0, FIXED_SIZE);

    Serial.println(esid.length());
    Serial.print("SSID: ");
    Serial.println(esid);
}

void setup() {
    Serial.begin(9600);
    EEPROM.begin(512); // Initialize EEPROM with the required size

    writeEEPROM();
    readEEPROM();
}

void loop() {
}
