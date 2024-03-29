#include <Arduino.h>
#include "SPIFFS.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "Configuration.h"

class Bootstrapper
{
    public:
    static void waitForSerial() {
        Serial.begin(115200);
        Serial.setTimeout(2000);

        while (!Serial) { }
    }

    static void setupWifi()
    {
        WiFi.softAP(ssid);
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
    }

    static void initializePins() {
        pinMode(FL1, OUTPUT);  
        pinMode(FL2, OUTPUT);

        pinMode(FR1, OUTPUT);  
        pinMode(FR2, OUTPUT);

        pinMode(BL1, OUTPUT);  
        pinMode(BL2, OUTPUT);

        pinMode(BR1, OUTPUT);  
        pinMode(BR2, OUTPUT);

        // Setup the PWM for the selected pins
        int frequency = 5000;
        int resolution = 8;
  
        ledcSetup(pwmChannelL, frequency, resolution);
        ledcAttachPin(FL2, pwmChannelL);
        ledcAttachPin(BL2, pwmChannelL);

        ledcSetup(pwmChannelR, frequency, resolution);
        ledcAttachPin(BR2, pwmChannelR);        
        ledcAttachPin(FR2, pwmChannelR);
    }

    static void initializeFilesystem() {
          if(!SPIFFS.begin(true)){
            Serial.println("An Error has occurred while mounting SPIFFS");
            return;
        }
    }
};