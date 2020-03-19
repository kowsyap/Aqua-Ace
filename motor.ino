#include "ThingSpeak.h"

#include <ESP8266WiFi.h> 

#define motor 13
 
#include <MyRealTimeClock.h>  
WiFiClient  client;

unsigned long myChannelNumber = 863955;
const char * myWriteAPIKey = "1MDSUFCOV25NTRAT";
const char ssid[] =  "One plus 6T";  // replace with your wifi ssid and wpa2 key
const char pass[] =  "Neversettle";
const char server[] = "api.thingspeak.com";
int maximumRange = 200; // Maximum range needed
int minimumRange = 12; // Minimum range needed

MyRealTimeClock myRTC(4,5,6);

void setup() {
 Serial.begin (115200);
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);
   pinMode(motor, OUTPUT);
 // seconds, minutes, hours, day of the week, day of the month, month, year
 myRTC.setDS1302Time(00, 59, 23, 6, 13, 9, 2019);
}

void loop() {
  myRTC.updateTime(); 
 WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      if(WiFi.status() == WL_CONNECTED){

  Serial.println("\nConnected.");     
      delay(5000);     
    } 
  long height = ThingSpeak.readLongField(myChannelNumber,1,myWriteAPIKey);  

 Serial.println("HEIGHT = ");
 Serial.println(height);
    if (height < maximumRange-minimumRange) {
      if((myRTC.hours==8 || myRTC.hours==13 || myRTC.hours==17)&&myRTC.minutes==00) {
      Serial.println("peak times");
      digitalWrite(motor, HIGH); 
     }
    }
    else if (height >= maximumRange-minimumRange){
      Serial.println("tank is full");
     digitalWrite(motor, LOW);
    }
    else if (height <= minimumRange){
     Serial.println("tank is empty");
     digitalWrite(motor, HIGH); 
    }
 delay(20000);
}
