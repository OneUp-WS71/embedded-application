#ifndef RESPIRATORYRATESENSOR_H
#define RESPIRATORYRATESENSOR_H

#include <Arduino.h>

class RespiratoryRateSensor {
public:
    RespiratoryRateSensor(uint8_t pin);
    float readRespiratoryRate();

private:
    uint8_t pin;
};

#endif
