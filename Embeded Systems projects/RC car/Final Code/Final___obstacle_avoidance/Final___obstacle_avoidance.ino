#include <elapsedMillis.h>



//motor A

#define in1 8
#define in2 9
//motor b

#define in3 10
#define in4 11
int r, c, l ;
const int trigPin = 2;
const int echoPin = 6;
int led = 13;
int h=1;
int S1=5 , S2=3;//Capital S
long duration;
int distance;
char estado ;
unsigned int interval = 500;
  elapsedMillis timeElapsed;
void setup() {
Serial.begin(9600);
pinMode(S1,OUTPUT);
pinMode(S2,OUTPUT);
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
l=analogRead(A3);
c=1000-analogRead(A4);
r=analogRead(A5);
 Serial.print("l  ");
    Serial.println(analogRead(A3));
  Serial.print("c  ");
  Serial.println(1000-analogRead(A4));
  Serial.print("r  ");
  Serial.println(analogRead(A5));




  
if(Serial.available()>0){ 
estado = Serial.read();
Serial.println("bt " + estado);
} 

if(estado=='L'){
 Max();
left ();

}

else if (estado=='R'){
  Max();
right ();
 
}
else if(estado=='F')
{
  Max();
forward ();

if (distance<=18)
 {

   
   while(timeElapsed<interval)
   {
  digitalWrite(13, HIGH);
  back();
   delay(500);
  right();
    delay(300);
   forward();
    delay(500);
    left();
   delay(300);
    forward();
   delay(1000);
    left();
    delay(300);
    forward();
    delay(500);
    right();
    delay(300);
   }
   
   timeElapsed=0;
    digitalWrite(led,LOW);
 Stop();
  
  

  }
}
else if (estado=='B')
{
  Max();
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
 
  
  
void Max()
{
  analogWrite(S1,255);
  analogWrite(S2,255);
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
   /* if (timeElapsed<interval)
    {
    analogWrite(S1,(5+timeElapsed/10));
    analogWrite(S2,(5+timeElapsed/10));
    }
    else if ((timeElapsed/10)>250)
     {
    analogWrite(S1,255);
    analogWrite(S2,255);
    }*/
 
      analogWrite(S1,230); analogWrite(S2,230);
    h=1;
    forward();
     Serial.println("FFFFFF");
  }
 else if(r > 500 && c < 500 && l < 500)
  {
   analogWrite(S1,185); analogWrite(S2,185);
  h=2;
   digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);
 Serial.println("RRRRRRRR");
    
  }
  

  else if(l > 500 && c<500 && r <500)
  {
     analogWrite(S1,185); analogWrite(S2,185);
   h=3;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
    Serial.println("LLLLLLLLLLL");
   }
 else if ( l + r + c > 2000)
 {
       analogWrite(S1,230); analogWrite(S2,230);
  h=1;
  forward();
  Serial.println("AAAAAAAAAAA");
  }
  
  else 
  {
    if (h==1)
    { analogWrite(S1,185); analogWrite(S2,185);digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);Serial.println("EEEEEEE1111111");}
    if (h==2)
    { analogWrite(S1,185); analogWrite(S2,185); digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);Serial.println("EEEEEEEEEE222222222");}
    if (h==3)
    { analogWrite(S1,185); analogWrite(S2,185); digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW);Serial.println("EEEEEEEE3333333333");}
}
  
  }
