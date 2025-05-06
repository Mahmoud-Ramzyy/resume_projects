
#include <elapsedMillis.h>
elapsedMillis timeElapsed=0;
unsigned int interval = 1500;
void setup() {
  pinMode(9,OUTPUT);

}

void loop() {

 while (timeElapsed <= interval) {
  digitalWrite(9,HIGH);
  } 
  while (timeElapsed <= (interval+interval)){
   digitalWrite(9,LOW);}
   timeElapsed=0;

     
 

}
