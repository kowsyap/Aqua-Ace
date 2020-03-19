#include "ThingSpeak.h"

#include <ESP8266WiFi.h> 

#define echoPin 0
#define trigPin 2  

long duration, distance,height;

WiFiClient  client;

unsigned long myChannelNumber = 863955;
const char * myWriteAPIKey = "1MDSUFCOV25NTRAT";
const char ssid[] =  "One plus 6T";  // replace with your wifi ssid and wpa2 key
const char pass[] =  "Neversettle";
const char server[] = "api.thingspeak.com";
int maximumRange = 200;


void setup() {
Serial.begin (115200);
WiFi.mode(WIFI_STA); 
ThingSpeak.begin(client);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 
}

void loop() {

 // Connect or reconnect to WiFi

   WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      if(WiFi.status() == WL_CONNECTED){

  Serial.println("\nConnected.");     
      delay(5000);     
    } 
 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

 digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);

 distance = duration/58.2;//in cm
 height = maximumRange-distance;

 Serial.println("HEIGHT = ");
 Serial.println(height);

  int x = ThingSpeak.writeField(myChannelNumber, 1, height, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
delay(20000);
}
