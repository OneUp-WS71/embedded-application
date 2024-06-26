#include "Device.h"

// Definiciones de WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverName = "https://elderlycareedge.azurewebsites.net/";

// Crear objeto Device
Device device(ssid, password, serverName);

void setup() {
    device.begin();
}

void loop() {
    device.run();
}
