#include <elapsedMillis.h>



//motor A

#define in1 8
#define in2 9
//motor b

#define in3 10
#define in4 11
int r, c, l ;
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
pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
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
l=1000-analogRead(A3);
c=analogRead(A4);
r=analogRead(A5);
 Serial.print("l  ");
  Serial.println(1000-analogRead(A3));
  Serial.print("c  ");
  Serial.println(analogRead(A4));
  Serial.print("r  ");
  Serial.println(analogRead(A5));



  
if(Serial.available()>0){ 
estado = Serial.read();
Serial.println("bt " + estado);
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

if (distance<=15)
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
else if (estado=='V')
{
  
lf ();

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
    {
      
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

 
  
 void lf ()
  {
  
      if(c > 700 && r < 700 && l < 700)
  {
    forward();
  }
 else if(r > 700 && c < 700 && l < 700)
  {
  right();
  }
  

  else if(l > 700 && c<700 && r <700)
  {
   left();
   }
 else if ( l + r +c >2100)
 {
  forward();
  }
  else 
  {
    Stop();

 }
  
  }
