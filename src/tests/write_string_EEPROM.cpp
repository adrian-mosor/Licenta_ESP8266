#include <EEPROM.h>
#include <Arduino.h>

#define ADRESS_TEST 100
#define FIXED_SIZE 6 // qsid length

void writeEEPROM(int offset, String str)
{
    // EEPROM.begin(100);
    EEPROM.put(offset, str);
    EEPROM.commit(); // save changes to EEPROM

    Serial.print("Wrote to EEPROM: ");
    Serial.println(str);

    // EEPROM.end();
}

void readEEPROM(int offset)
{
    // EEPROM.begin(100);

    String strread;
    EEPROM.get(offset, strread);
    strread = strread.substring(0, FIXED_SIZE);

    Serial.print("Extracted length from EEPROM: ");
    Serial.println(strread.length());
    Serial.print("Extracted string from EEPROM: ");
    Serial.println(strread);

    // EEPROM.end();
}

void setup()
{
    Serial.begin(9600);
    EEPROM.begin(128); // Initialize EEPROM with the required size

    // writeEEPROM();
    // readEEPROM();

    String qsid = "Welc20";
    writeEEPROM(ADRESS_TEST, qsid);
    readEEPROM(ADRESS_TEST);
}

void loop()
{
}

// raw functions:
void writeEEPROM()
{
    String qsid = "Global";

    Serial.println("writing eeprom ssid:");
    EEPROM.put(ADRESS_TEST, qsid);
    EEPROM.commit();
    Serial.print("Wrote: ");
    Serial.println(qsid);
}

void readEEPROM()
{
    Serial.println("Reading EEPROM ssid");
    String esid;

    EEPROM.get(ADRESS_TEST, esid);
    esid = esid.substring(0, FIXED_SIZE);

    Serial.println(esid.length());
    Serial.print("SSID: ");
    Serial.println(esid);
}
