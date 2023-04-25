#pragma once

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

extern WiFiClient client;

// Set WiFi credentials

#define WIFI_SSID "Lasting-Software"
#define WIFI_PASS "Soft@Lasting123"

// #define WIFI_SSID "303B"
// #define WIFI_PASS "adi123456"   

void setup_Wifi();

// Object ID String for dweet: smart_matrix_esp8266
void send_IP_to_dweet(String ESP8266IP);