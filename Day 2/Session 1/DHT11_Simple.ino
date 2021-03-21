#include <DHT.h>

#define DHTtype DHT11
#define DHT_pin D3


DHT dht(DHT_pin, DHTtype);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature(); //Reading Temperature
  float h = dht.readHumidity(); //Reading Humidity
  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Humidity: ");
  Serial.println(h);
  delay(800);
}
