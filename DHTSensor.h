#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <DHT.h>
#include <DHT_U.h>

class DHTSensor {
public:
    DHTSensor(uint8_t pin, uint8_t type);
    void begin();
    float readTemperature();

private:
    DHT dht;
};

#endif
