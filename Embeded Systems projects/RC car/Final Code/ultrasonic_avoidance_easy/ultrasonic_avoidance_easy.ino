#include <elapsedMillis.h>
//motor A

#define in1 8
#define in2 9
//motor b

#define in3 10
#define in4 11

const int trigPin = 3;
const int echoPin = 6;
int led = 13;
long duration;
int distance;
char estado ;
unsigned int interval = 1000;
  elapsedMillis timeElapsed;
void setup() {
Serial.begin(9600);
 pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(led, OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}
void loop() {
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
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
digitalWrite(led,LOW);



  
if(Serial.available()>0){ 
estado = Serial.read();
} 

if(estado=='L'){ 
left ();

}

else if (estado=='R'){
right ();
 
}
else if(estado=='F')
{
forward ();

if (distance<=18)
 {

   
   while(timeElapsed<interval)
   {
   digitalWrite(13, HIGH);
  back();
   }
   timeElapsed=0;
    digitalWrite(led,LOW);
 Stop();
  
  

  }
}
else if (estado=='B')
{
back();
}
else 
{
  Stop();
  }
}
 
  
  

  void forward ()
    {
     digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);}
      void back ()
    {
      digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);}
      void right ()
    {Serial.println("right");
      digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);}

 
      void left ()
 {
     digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);}

  
      void Stop ()                //care to 's' char in stop ----> capital
{
     digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);}

 
  


