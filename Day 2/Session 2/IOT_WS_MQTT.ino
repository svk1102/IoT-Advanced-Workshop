#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define Button 5

uint8_t flag=1;

const char* ssid = "Flash"; //Top class wifi name
const char* password = "iamtheflash"; //Well now you can come chill at my home, mera password jo mil gaya tumko garebo

const char* mqtt_server = "m15.cloudmqtt.com"; // Ye humara Third Party hai, isko mei BROKER bolta hu

WiFiClient espClient; // Object is being created
PubSubClient client(espClient); //Object is created whose Constructor takes Object created above as parameters


#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

char* value;

void setup_wifi() {

  delay(10);
  // Chalo connection shuru krte hai
  Serial.println();
  Serial.print("Connecting to "); // Kuch Serial Monitor mei Print bhi kar lete hai
  Serial.println(ssid); 

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  // Agar aap baju wale ka internet use krr rhe ho toh ho skta hai ye command nahi chale ;-/

  while (WiFi.status() != WL_CONNECTED) { // Let's go for a coffee while it gets connected (Winkss)
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // Muskuriye aapka WiFi Makhan Chalra hai
}

void callback(char* topic, byte* payload, unsigned int length) {  // Message yaha receive krne k liye mei ye use krunga
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(2, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Yaha ghumna padega agar aap JIO ka Network use krre ho
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Let's try connecting to the broker coz ladki se toh ghanta hi connect kr paaeynge
    if (client.connect("woncsgkx","woncsgkx","9-NM2VP_gV_R")) {
      Serial.println("connected");
      // Ab Connect ho gye hai toh thodi baat cheet bhi kr lete hai
      client.publish("HumaraTopic", "Humara Sabse Pehla Message"); 
      // Baatein Sunni bhi padegi
      client.subscribe("inTopic");
    } else {
      // Sorry par aap zindagi ke sath yaha bhi fail ho chuke ho
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Par kisi mahan vyakti (Prithvi Shetty @iamprithvishetty :- Follow me on insta ad I'll make sure I don't accept your follow request) ne kaha hai dobara koshish jaari rakhni chaiye
      delay(5000);
    }
  }
}

void setup() {
  pinMode(2, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(Button, INPUT);
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 14786);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  Serial.println(digitalRead(Button));
  if (flag==0 and digitalRead(Button)==1) //Specify the timing between every data send
  {
    value = "PRITHVI SHETTY";
    //snprintf (msg, MSG_BUFFER_SIZE, "esp1-%s", value.c_str());
    Serial.print("Publish message: ");
    Serial.println(value);
    client.publish("HumaraTopic", value);
    flag = 1;
  }
  else if(digitalRead(Button)==0)
  {
    flag=0;
  }
  
}
