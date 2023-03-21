#include "wireless_conn.h"

void setup_Wifi(){

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
}