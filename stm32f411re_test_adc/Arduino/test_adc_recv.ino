#include <SoftwareSerial.h>
#include "stdint.h"

SoftwareSerial Serial2(10, 11); //Rx, Tx

int speed = 115200;
uint16_t val;
float float_val;
bool get16bytes = false;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("Let's get started!");
}

void loop() {
  #if 0
    if(Serial2.available()){
      int c = Serial2.read();
      Serial.print(char(c));
    }
  #else
    if(Serial2.available()){
      if(get16bytes){
        val |= (Serial2.read()<<8);
        float_val = val*(3.3/4096);
        Serial.println(float_val);
        get16bytes = false;
      }else{
        val = Serial2.read();
        get16bytes = true;
      }
    }
  #endif
}
