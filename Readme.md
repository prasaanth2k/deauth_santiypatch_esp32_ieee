# Deauth Patch for PlatformIO ESP32 WiFi Library
## Version 6.10.0

### Background

In the Espressif ESP32 WiFi library, there are built-in restrictions that prevent sending certain raw WiFi frames. When attempting to send a deauthentication frame, you might encounter an error:

```text
wifi:unsupport frame type: 0c0
```

This error occurs due to the WiFi library's sanity check function `ieee80211_raw_frame_sanity_check()`, which implements WiFi policy and legal restrictions.

### Patch Motivation

The sanity check function limits the transmission of raw frames like deauthentication frames. This patch allows bypassing these restrictions.

### Detailed Procedure

#### Prerequisites
- PlatformIO
- Ubuntu (or similar Linux environment)
- Basic reverse engineering knowledge

#### Installation Steps

1. Install PlatformIO:
   ```bash
   pip install platformio
   ```
   Recommended: Use a virtual environment for maintainability

2. Extract the WiFi library:
   ```bash
   cd ~/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/lib
   mkdir extracted_net80211
   cd extracted_net80211
   ar x ../libnet80211.a
   ```

3. Locate the target file:
   - Look for `ieee80211_output.o` in the extracted files
   - Disassemble and modify the `ieee80211_raw_frame_sanity_check()` function
   - Fill checks with NOPs
   - Modify function to return 0

4. Repack the library:
   ```bash
   ar rcs ../libnet80211.a *.o
   mv ../libnet80211.a ~/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/lib/libnet80211.a
   ```

### Additional Resources

Detailed reverse engineering content is available on the myblog blog: [BLOG](https://prasaanth2k.github.io/posts/WiFi-Deauthentication-Attack-with-ESP32-Wroom/)

### Disclaimer

**For educational purposes only. Ensure compliance with local regulations and ethical guidelines.**
