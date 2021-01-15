//온도센서
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//블루투스센서
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11);
//RX:11, TX:10 => 연결 반대로

//릴레이모듈
int Relay = 3;

int tempDelay = 5;
int lastMillis = 0;

int h = 0;
int t = 0;

void setup()
{
 Serial.begin(9600);//시리얼 초기화
 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 Serial.println("Serial Conn!");
 bluetooth.begin(9600); //소프트웨어 시리얼 통신

 pinMode(Relay, OUTPUT); //Set Pin3 as output
}

char android;

void loop()
{
  if(bluetooth.available()){
    android = bluetooth.read();

    delay(500);
    
    Serial.write(android);
  
  }

  if(Serial.available()){
    bluetooth.write(Serial.read());
  }









  
//  if(millis()/1000 - lastMillis > tempDelay){
//      lastMillis = millis()/1000;
//      
//      h = dht.readHumidity();
//      t = dht.readTemperature();
//      Serial.print("Humidity: ");
//      Serial.print(h);
//      Serial.print(" %\t");
//      Serial.print("Temperature: ");
//      Serial.print(t);
//      Serial.println(" C");
//  }
//
//  if(t <= 35){
//      digitalWrite(Relay, HIGH); //Turn off relay
//  }else{
//      digitalWrite(Relay, LOW); //Turn on relay
//  }
  

} 
