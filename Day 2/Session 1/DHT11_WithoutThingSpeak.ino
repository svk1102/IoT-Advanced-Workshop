#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

DHT dht(D3, DHT11);

String host = "api.thingspeak.com";
int httpPort = 80;  
String url1 = "/update?api_key=ZSYLSCCPICFFXCLZ&field1=";
String url2 = "/update?api_key=ZSYLSCCPICFFXCLZ&field2=";

HTTPClient http; 

void setup() 
{
  Serial.begin(9600);
  WiFi.begin("WiFi Username", "WiFi Password"); //Enter your own WiFi credentials
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);

  //Sending data to ThingSpeak using GET request
  url1 = url1 + (String) t;
  http.begin(host,httpPort,url1); 
  int httpCode = http.GET();
  Serial.println(httpCode); //200 if its working
  delay(2000);

  url2 = url2 + (String) h;
  http.begin(host,httpPort,url2); 
  httpCode = http.GET(); //200 if its working 
  Serial.println(httpCode);
  delay(2000);
}
