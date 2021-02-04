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

int t = 0;

bool warmerOn = false;    //app에서 warmer button의 On/Off 상태
bool relayOn = false;     //arduino에서 relay의 On/Off 상태

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

void loop()
{
  if(millis()/1000 - lastMillis > tempDelay){
    lastMillis = millis()/1000;
    t = dht.readTemperature();
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" C");
  }

  if(bluetooth.available()){
    char input = bluetooth.read();
    
    switch(input){
      case '1' :
        Serial.println("Warmer On");
        digitalWrite(Relay, HIGH);
        warmerOn = true;
        relayOn = true;
        break;
      case '2' :
        Serial.println("Warmer Off");
        digitalWrite(Relay, LOW);
        warmerOn = false;
        relayOn = false;
        break;
      case '3' :
        byte bytes[5];
        bytes[0] = relayOn;
        
        bytes[1] = (t >> 24) & 0xFF;
        bytes[2] = (t >> 16) & 0xFF;
        bytes[3] = (t >> 8) & 0xFF;
        bytes[4] = t & 0xFF;
        
        bluetooth.write(bytes, 5);
        
        break;
    } 

    if(warmerOn && relayOn){
       if(t >= 30){
          digitalWrite(Relay, LOW);
          warmerOn = true;
          relayOn = false;
       }
    }else if(warmerOn && !relayOn){
       if(t <= 27){
          digitalWrite(Relay, HIGH);
          warmerOn = true;
          relayOn = true;
       }
    }
    
    delay(500);
  }
} 
