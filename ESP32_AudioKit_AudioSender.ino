/*
Simple Wireless Mic V0.1
Slider2732_ Nov 2026

AC101 input selection
ADC_INPUT_LINE1	Microphone input
ADC_INPUT_LINE2	Line input
ADC_INPUT_LINE3	Right microphone + left line input
ADC_INPUT_ALL	Both microphone and line inputs
*/



#include "AudioTools.h"
#include "AudioTools/AudioLibs/AudioBoardStream.h"
#include <WiFi.h>
#include <WiFiUdp.h>

// Wi-Fi details
const char* WIFI_SSID = "";  // Your network name 
const char* WIFI_PASSWORD = ""; // Your WiFi password

// PC details
const char* PC_IP = "192.168.1.100";  // Change this to your PC's network ID. Use Terminal: hostname -I
const uint16_t UDP_PORT = 12345;

WiFiUDP udp;

// This works with Audio Kits using the AC101 CODEC
AudioBoardStream kit(AudioKitAC101);

// 640 samples = 1280 bytes = approximately 20ms
int16_t buffer[640];

uint32_t packetCount = 0;

void setup() {
  Serial.begin(115200);

  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);

  // Start audio capture
  auto cfg = kit.defaultConfig(RX_MODE);
  cfg.sd_active = false;
  cfg.input_device = ADC_INPUT_LINE1;
  cfg.sample_rate = 16000; 
  cfg.channels = 2;
  cfg.bits_per_sample = 16;

  if (!kit.begin(cfg)) {
    Serial.println("Audio Kit initialisation failed!");
    while (true) delay(1000);
  }

  Serial.println("Audio input started");

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(12346);
  Serial.println("Starting UDP audio stream");
}

void loop() {
  size_t bytes = kit.readBytes(
    (uint8_t*)buffer,
    sizeof(buffer)
  );

  if (bytes > 0) {
    udp.beginPacket(PC_IP, UDP_PORT);
    udp.write((uint8_t*)buffer, bytes);
    udp.endPacket();

    packetCount++;

    // Occasional progress report, not continuous serial output
    if (packetCount % 50 == 0) {
      Serial.print("Packets sent: ");
      Serial.println(packetCount);
    }
  }
}
