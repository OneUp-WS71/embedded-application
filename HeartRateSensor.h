#ifndef HEARTRATESENSOR_H
#define HEARTRATESENSOR_H

#include <Arduino.h>

class HeartRateSensor {
public:
    HeartRateSensor(uint8_t pin);
    float readHeartRate();

private:
    uint8_t pin;
};

#endif
