#include <ESP8266WiFi.h>  // Add this library
#include "DHT.h"

#define DHT11_PIN 4
DHT dht(DHT11_PIN, DHT11);

void setup() {
  Serial.begin(115200); // Change the baud rate to 115200
  dht.begin();
}

void loop() {
  delay(3000); // DHT11 needs at least 2 seconds to stabilize

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(1000);
}
