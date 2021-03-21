#include <DHT.h>

#define DHTtype DHT11
#define DHT_pin D3


DHT dht(DHT_pin, DHTtype); // Defining DHT type and pin

void setup() {
  // put your setup code here, to run once:
  dht.begin(); // Beginning DHT11 Sensor
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature(); // Read temperature
  float h = dht.readHumidity(); // Read Humidity
  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Humidity: ");
  Serial.println(h);
  delay(800);
}
