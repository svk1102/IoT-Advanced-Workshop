#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// defines pins numbers
#define trigPin D1  //D4
#define echoPin D2  //D3

// defines variables
long duration;
long distance;

char auth[] = "your_auth_code";
char ssid[] = "your_wifi_username";
char pass[] = "your_wifi_password";

void setup() {

Blynk.begin(auth, ssid, pass);
  
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
  Blynk.run();
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
Blynk.virtualWrite(V5, distance);
if (distance <= 10){
    Blynk.notify("ESP8266 Alert -> distance <= 10");
  }
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
Serial.println(distance);
delay(500);
}
