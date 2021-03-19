#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define PIR D5  
int PIRstate = 0;
int i;


void setup () {
  Serial.begin(9600);

  pinMode(PIR, INPUT); //digitalWrite(PIR, LOW);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("PIR is Stabilizing");
  while(i != 30){
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

  if (PIRstate == HIGH)  //Checking if there is any motion
  {
    Serial.println();
    Serial.println("Alert !!!");
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(200);
  }

}
