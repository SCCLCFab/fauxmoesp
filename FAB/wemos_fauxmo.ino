//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include "credentials.h"
 
#define SERIAL_BAUDRATE                 115200
#define RELAY_PIN1  D4 //Note: does not recognize 'BUILTIN_LED'
#define RELAY_PIN2  D2
 
fauxmoESP fauxmo;
 
// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------
 
void wifiSetup() {
 
    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);
 
    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
 
    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
 
    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
 
}

void callback(unsigned char device_id, const char * device_name, bool state) {
  Serial.print("Device ID "); Serial.print(device_id);
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");

  if ( (strcmp(device_name, "light one") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(RELAY_PIN1, LOW);
      Serial.println("OFF");
    } else {
      digitalWrite(RELAY_PIN1, HIGH);
      Serial.println("ON");
    }
  }

  if ( (strcmp(device_name, "light two") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(RELAY_PIN2, HIGH);
      Serial.println("ON");
    } else {
      digitalWrite(RELAY_PIN2, LOW);
      Serial.println("OFF");
    }
  }
}

void setup() {
 
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println();

   // Initialize pin BUILTIN_LED and D3
   pinMode(RELAY_PIN1,OUTPUT);
   digitalWrite(RELAY_PIN1,LOW);
   pinMode(RELAY_PIN2,OUTPUT);
   digitalWrite(RELAY_PIN2,LOW);
  
    // Wifi
    wifiSetup();
 
    // Fauxmo v2.0
    fauxmo.addDevice("light one");
    fauxmo.addDevice("light two");
    fauxmo.onMessage(callback);
}
 
void loop() {
    fauxmo.handle();
}
