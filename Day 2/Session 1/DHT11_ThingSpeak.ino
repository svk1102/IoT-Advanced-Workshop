#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#include "ESP8266WiFi.h"
#include <ThingSpeak.h>

#define DHTTYPE DHT11   // DHT 11
#define dht_dpin D3
DHT dht(dht_dpin, DHTTYPE); 

WiFiClient client;

long myChannelNumber = 1334140; //ThingSpeak Channel No.
const char myWriteAPIKey[] = "ZSYLSCCPICFFXCLZ"; //ThingSpeak Write API Key

void setup(void)
{ 
  dht.begin();
  Serial.begin(9600);
  WiFi.begin("Wifi Username", "Wifi Password"); //Enter your own WiFi credentials
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  Serial.println("Humidity and temperature\n\n");
  delay(700);

  ThingSpeak.begin(client);

}
void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey); //Writing data to ThingSpeak server
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey); //Writing data to ThingSpeak server
    
  delay(800);
}
