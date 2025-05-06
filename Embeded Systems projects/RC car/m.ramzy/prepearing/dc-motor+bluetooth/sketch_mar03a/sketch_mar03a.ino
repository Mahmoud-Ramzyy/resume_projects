#include <SoftwareSerial.h>
SoftwareSerial myserial (0,1);
int m1=A0;  // motor is connected to the analog pin A0 of arduino
int h=255;  // this is 5 volt
int l=0;    // this is  0 volt
String motion;



void setup() {
  Serial.begin(9600);
  pinMode(m1,OUTPUT);
}

void loop() {
  Serial.println("Please enter 'w' for forward,'s' for stop ");
  while(Serial.available()==0){   }
  
  motion=Serial.readString();
  if(motion=="w"){
  analogWrite(m1,l);
  }

  if(motion=="s"){
  analogWrite(m1,h);
  }
}
