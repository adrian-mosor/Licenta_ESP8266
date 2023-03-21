// Connect esp8266 to Wi-Fi

#include <ESP8266WiFi.h>
#include <Arduino.h>

// Set WiFi credentials
#define WIFI_SSID "Lasting-Software"
#define WIFI_PASS "Soft@Lasting123"

void setup()
{
  // Setup serial port
  Serial.begin(9600);
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off

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
    // Serial.print(".");
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (Note that LOW is the voltage level
                                  // LED indicating that connection to internet is working
}

void loop()
{
  // put your main code here, to run repeatedly:
}