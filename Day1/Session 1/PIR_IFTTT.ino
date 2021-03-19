#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define PIR D5  
int PIRstate = 0;
int i;

void setup () {
  //Setting up Serial Monitor and WiFi
  Serial.begin(9600);
  WiFi.begin("Your wifi name","Password");
  
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(400);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Nodemcu is connected");

  pinMode(PIR, INPUT);                         //Configure PIR pin as input to read
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("PIR is Stabalizing"); 
  while(i != 30)                              // Wait for 30 Seconds 
  {
    i=i+1;
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println();
  Serial.print("PIR is ready to use");
}

void loop()
{ 
  PIRstate = digitalRead(PIR);

  if (PIRstate == HIGH)                       //Check if there is any motion
  {
    Serial.println();
    Serial.println("Alert !!!");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    if (WiFi.status() == WL_CONNECTED)        //Check WiFi connection status
    {
      HTTPClient http;                        //Declare an object of class HTTPClient
      http.begin("Your Ifttt link");  //Specify request destination
      http.GET();                             //Send GET request
      http.end();                             //Close the connection
      Serial.println();
      Serial.println("Alert Sent");           //Confirmation after sending alert to IFTTT
      delay(3000);
    }   
  }
}
