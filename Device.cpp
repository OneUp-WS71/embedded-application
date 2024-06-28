#include "Device.h"

// Definiciones de pines y tipos de sensores
#define DHTPIN 15
#define DHTTYPE DHT22
#define HEARTBEATPIN 34
#define LDRPIN 35 // Pin para el sensor de luz

Device::Device(const char* ssid, const char* password, const char* serverName)
  : ssid(ssid), password(password), serverName(serverName),
    dhtSensor(DHTPIN, DHTTYPE), heartRateSensor(HEARTBEATPIN),
    respiratoryRateSensor(LDRPIN), lcd(27, 32, 33, 21, 22, 23, 26) {}

void Device::begin() {
    Serial.begin(115200);
    dhtSensor.begin();
    lcd.begin(16, 2);

    connectWiFi();
}

void Device::connectWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void Device::sendData(float temperature, float heartbeat, float respiratoryRate, float latitude, float longitude) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverName + String("/api/Elderlycare/v1/report?patientId=3"));
        http.addHeader("Content-Type", "application/json");

       String jsonPayload = "{";
        jsonPayload += "\"id\": 0,";
        jsonPayload += "\"heartRate\":" + String(heartbeat,1) + ",";
        jsonPayload += "\"breathingFrequency\":" + String(respiratoryRate,1) + ",";
        jsonPayload += "\"temperature\":" + String(temperature,1) + ",";
        jsonPayload += "\"longitude\":\"" + String(longitude, 6)+ "\",";
        jsonPayload += "\"latitude\":\"" + String(latitude, 6)+ "\"";
        jsonPayload += "}";

        Serial.println("Payload: " + jsonPayload);

        int httpResponseCode = http.POST(jsonPayload);
        
        Serial.println("HTTP Response code: " + String(httpResponseCode));

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        } else {
            Serial.println("Error on sending POST: " + String(httpResponseCode));
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }
}

void Device::run() {
    float adjustedTemperature = dhtSensor.readTemperature();
    float heartbeat = heartRateSensor.readHeartRate();
    float respiratoryRate = respiratoryRateSensor.readRespiratoryRate();

     // Generar coordenadas GPS aleatorias en Lima
int min_lat_micro = -12080000;   // Alrededor de -12.08 * 1000000
int max_lat_micro = -12070000;   // Alrededor de -12.07 * 1000000
int min_lng_micro = -77095000;   // Alrededor de -77.095 * 1000000
int max_lng_micro = -77085000;   // Alrededor de -77.085 * 1000000

float latitude = random(min_lat_micro, max_lat_micro) / 1000000.0;
float longitude = random(min_lng_micro, max_lng_micro) / 1000000.0;

    static int screen = 0;
    lcd.clear();

    if (screen == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(adjustedTemperature);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("Heart: ");
        lcd.print(heartbeat);
        lcd.print(" bpm");
    } else if (screen == 1) {
        lcd.setCursor(0, 0);
        lcd.print("Resp: ");
        lcd.print(respiratoryRate);
        lcd.print(" rpm");
    } else {
        lcd.setCursor(0, 0);
        lcd.print("Lat: ");
        lcd.print(latitude, 6);
        lcd.setCursor(0, 1);
        lcd.print("Lon: ");
        lcd.print(longitude, 6);
    }
    screen = (screen + 1) % 3; // Alternar entre las tres pantallas

    sendData(adjustedTemperature, heartbeat, respiratoryRate, latitude, longitude);

    delay(10000); // Esperar 10 segundos antes de la próxima lectura
}
