#include <SoftwareSerial.h>
SoftwareSerial myserial(1,2);
char data;

void setup() {
 myserial.begin(9600);

 pinMode(12,OUTPUT);

}

void loop() {
  if(Serial.available ()>0)

{data=Serial.read();
Serial.print(data);
Serial.print("");
if(data=='1'){
digitalWrite(12,HIGH);
Serial.print("led:on");}
else if(data=='0'){
digitalWrite(12,LOW);
Serial.print("led:off");}
}

}
