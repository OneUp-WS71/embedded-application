#include "RespiratoryRateSensor.h"

RespiratoryRateSensor::RespiratoryRateSensor(uint8_t pin) : pin(pin) {}

float RespiratoryRateSensor::readRespiratoryRate() {
    int ldrValue = analogRead(pin);
    return map(ldrValue, 0, 4095, 12, 20); // Simula bpm entre 12 a 20 rpm
}
