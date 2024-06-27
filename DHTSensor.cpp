#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

void DHTSensor::begin() {
    dht.begin();
}

float DHTSensor::readTemperature() {
    float t = dht.readTemperature();
    if (isnan(t)) {
        Serial.println("Error al leer el sensor DHT!");
        return NAN;
    }
    return map(t, 0, 50, 360, 370) / 10.0;// Ajustar la temperatura al rango de 36 a 37 grados Celsius
}
