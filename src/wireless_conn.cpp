#include "wireless_conn.h"

void setup_Wifi()
{

    // Setup serial port
    Serial.begin(9600);
    Serial.println();

    delay(1000);
    // Begin WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Connecting to WiFi...
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    // Loop continuously while WiFi is not connected
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }

    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);

    // Connected to WiFi
    Serial.println();
    Serial.print("Connected! IP address: (new function)");
    Serial.println(WiFi.localIP());
    send_IP_to_dweet(WiFi.localIP().toString());
}

void send_IP_to_dweet(String ESP8266IP)
{

    HTTPClient http;
    String dweet_url = "http://dweet.io/dweet/for/smart_matrix_esp8266?ip=";
    dweet_url += ESP8266IP;

    http.begin(client, dweet_url);
    int httpCode = http.GET();

    if (httpCode > 0)
    {

        String payload = http.getString();
        Serial.println("Dweet.io response:");
        Serial.println(payload);
    }
    else
    {

        Serial.println("Error sending data to dweet.io");
    }

    http.end();
}