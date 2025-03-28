#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>


uint8_t *frame;

// Callback function to process sniffed packets
void snifferCallback(void *buf, wifi_promiscuous_pkt_type_t type) {
    wifi_promiscuous_pkt_t *packet = (wifi_promiscuous_pkt_t *)buf;
    uint8_t *frame = packet->payload;
    // uint16_t len = packet->rx_ctrl.sig_len;
    // Serial.printf("Full Frame");
    // for (int i = 0; i < len; i++)
    // {
    //     Serial.printf("%02x",frame[i]);
    // }
    // Serial.println();
    
    // Extract source & destination MAC addresses
    uint8_t *destMac = frame + 4;   // Destination MAC
    uint8_t *srcMac = frame + 10;   // Source MAC
    uint8_t *bssid = frame + 16;    // BSSID (for beacon/data frames)

    Serial.print("AP (BSSID): ");
    for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", bssid[i]);
        if (i < 5) Serial.print(":");
    }

    Serial.print("  |  Client (MAC): ");
    for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", srcMac[i]);
        if (i < 5) Serial.print(":");
    }

    Serial.println();
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(snifferCallback);
    esp_wifi_set_channel(6, WIFI_SECOND_CHAN_NONE);  // Change channel as needed
    esp_wifi_set_promiscuous(true);
}

void loop() {
    delay(100);
}
