#include "HeartRateSensor.h"

HeartRateSensor::HeartRateSensor(uint8_t pin) : pin(pin) {}

float HeartRateSensor::readHeartRate() {
    int sensorValue = analogRead(pin);
    return map(sensorValue, 0, 4095, 60, 100); // Simula bpm entre 60 y 100 bpm 
}
