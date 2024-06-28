#ifndef DEVICE_H
#define DEVICE_H

#include <Adafruit_LiquidCrystal.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHTSensor.h"
#include "HeartRateSensor.h"
#include "RespiratoryRateSensor.h"

class Device {
public:
    Device(const char* ssid, const char* password, const char* serverName);
    void begin();
    void run();

private:
    const char* ssid;
    const char* password;
    const char* serverName;

    DHTSensor dhtSensor;
    HeartRateSensor heartRateSensor;
    RespiratoryRateSensor respiratoryRateSensor;
    Adafruit_LiquidCrystal lcd;

    void connectWiFi();
    void sendData(float temperature, float heartbeat, float respiratoryRate, float latitude, float longitude);
};

#endif
