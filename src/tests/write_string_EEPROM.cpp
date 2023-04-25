#include <EEPROM.h>
#include <Arduino.h>

#define ADRESS_TEST 100
#define FIXED_SIZE 16 // qsid length

void writeStringEEPROM(int offset, const String& str)
{
    EEPROM.put(offset, str);
    EEPROM.commit(); // save changes to EEPROM

    Serial.print("Wrote to EEPROM: ");
    Serial.println(str);
}

String readStringEEPROM(int offset)
{
    String strread;
    EEPROM.get(offset, strread);
    strread = strread.substring(0, FIXED_SIZE);

    Serial.print("Extracted length from EEPROM: ");
    Serial.println(strread.length());
    Serial.print("Extracted string from EEPROM: ");
    Serial.println(strread);

    return strread;
}

void setup()
{
    Serial.begin(9600);
    EEPROM.begin(256); // Initialize EEPROM with the required size

    // writeEEPROM();
    // readEEPROM();

    String qsid = "KPCTNSAJXKEBSPLS";
    String resstr;
    writeStringEEPROM(ADRESS_TEST, qsid);
    resstr = readStringEEPROM(ADRESS_TEST);

    Serial.print("FINAL resstr extracted: ");
    Serial.println(resstr);
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
