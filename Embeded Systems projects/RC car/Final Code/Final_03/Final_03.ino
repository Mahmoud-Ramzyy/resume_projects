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
int h=2;
int b=2;
int S1=5 , S2=3; //Capital S
long duration;
int distance;
char estado ;
int spd=255;
int spd0=180;
int lfd=400;
int f1,f2,f3,f4,f5,f6,ff,fff;
unsigned int interval = 1000;
float tcircle,omega,r3,r2,r1,v1,v2,N1,N2,d1,d2,t1,t2,pi=3.14,d,t, tanglerect1,tanglerect2,tangle,theta,V;
int i;
int j=0;  //switcher
int detect1=0;  //to detect if the turn on right or on left from the line track
int detect2=0;


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
void Max()
{
  analogWrite(S1,spd);
  analogWrite(S2,spd);
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

  void avoid()
  {
     back();
      delay(500);
  right();
    delay(300);
    if (distance <20)
    {
      Stop();
    }
     else {
   forward();
    delay(1000);
    left();
   delay(300); 
      Stop();
   /*    forward();
   delay(1000);
    left();
    delay(300); 
    
    forward();
    delay(500);
    right();
    delay(300);
    Stop();*/
    }
    }
    

 
 void lf ()
   {
      if((c > lfd && r < lfd && l < lfd )|| (c > lfd && r> lfd && l > lfd))
  {
   
 
      analogWrite(S1,spd ); analogWrite(S2,spd);
  h=1;
   
    forward();
     Serial.println("FFFFFF");
  }
 else if((r >lfd && c < lfd && l < lfd)||(r >lfd && c > lfd && l < lfd))
  {
   analogWrite(S1,spd0 ); analogWrite(S2,spd0);
  h=2;
  b=2;
   right();
 Serial.println("RRRRRRRR");
    
  }
  

  else if((l > lfd && c<lfd && r <lfd)||(l > lfd && c>lfd && r <lfd))
  {
   analogWrite(S1,spd0 ); analogWrite(S2,spd0);
   h=3;
   b=3;
  left();
  
    Serial.println("LLLLLLLLLLL");
   }
  
 else 
  {
    if (h==1)
    {  analogWrite(S1,spd0 ); analogWrite(S2,spd0); 

    right();
    /* if (b==2)
     {
     left();
    
   }
   else if (b==3)
   {
    right();
   }*/
     Serial.println("EEEEEEE1111111");
     }
    
    if (h==2)
    {  analogWrite(S1,spd0 ); analogWrite(S2,spd0);

  
   right();
   Serial.println("EEEEEEEEEE222222222");
    }
    if (h==3)
    {  
      
      analogWrite(S1,spd0 ); analogWrite(S2,spd0); 
      left();
      Serial.println("EEEEEEEE3333333333");
      }
     
}

}
void left2 ()
 {
  analogWrite(S2,100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);}

  void right2 () 
 
 {
 analogWrite(S1,100);
  
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);}  

 
 void lines ()
 { if (c>300 &&r<=300 &&l<=300 ||c>300 &&l<=300 &&r>300 ||c>300 &&r<=300 &&l>300)
  {while (c>300 &&r<=300 &&l<=300 ||c>300 &&l<=300 &&r>300 ||c>300 &&r<=300 &&l>300)
   { 
      Serial.print("7mra 1 11111 ");
      if (c>300 &&l<=300 &&r>300)
      {detect1=1;
      detect2=0;
        while (c>300 &&l<=300 &&r>300)
      {
       forward ();
       break;}}
       else if (c>300 &&r<=300 &&l>300)
      {detect1=0;
      detect2=1;
        while (c>300 &&r<=300 &&l>300)
      {
       forward ();
       break;}}
  else   {detect1=0;
      detect2=0;
        while (c>300 &&r<=300 &&l<=300)
      {
       forward ();
       break;}}
  
  
    break;
    }}
       else if (c<=300 &&r<=300 &&l>300)
       {while (c<=300 &&r<=300 &&l>300)
        {  
           Serial.print("7mra 222222  ");
          j=1;
        /*   if (c<=300)
           { while (c<=300)
             { Serial.print("7mra 2.111111  ");
              forward();
             break;}} */
              if (l>300 && c<=300 &&detect2==0)
           {  while (l>300 &&c<=300)
             { Serial.print("7mra 2.....222222  ");
              left2 ();
             break;
              }}
              else{ if (detect2==1&&l>300 &&c<=300)
              {  while (l>300 &&c<=300)
             { Serial.print("7mra 2.....222222  ");
              right2 ();
             break;
              }}detect2=0;}
              
             
               break;}}
              else if ( c<=300 &&l<=300 &&r>300)
               {while  (c<=300 &&l<=300 &&r>300)
               { 
          j=2;
          Serial.print("7mra 333333  ");
        /*  if (c<=300)
            {while (c<=300)
             {Serial.print("7mra 3.1111  ");
              forward();
             break;}} */
             if (r>300 &&c<=300)
            { while (r>300 &&c<=300)
             {
              Serial.print("7mra 3.22222  ");
              right ();
             break;
              }}
        
              break;}}
          else  if (c>300 &&r>300 &&l>300)
               {while(c>300 &&r>300 &&l>300)
        
                
      {  
            if (r>300 &&l>300)
            { while (r>300 &&l>300)
              {forward ();
              break;}}
               Serial.print("7mra 44444444  ");
          
            break;}
               }
        
      else  if (c<=300 &&r<=300 &&l<=300) 
            { while (c<=300 &&r<=300 &&l<=300)
             { 
        
           Serial.print("7mra 55555  ");
           if (r<=300&&j==1)
           {while (r<=300)
          { right ();
           Serial.print("7mra 5 hileft  ");
          break;}}
           if (j==2&&l<=300)
          { while (l<=300)
            {left ();
           Serial.print("7mra 5 hiright  ");
           break;}} 
           if (j==0&&l<=300 &&r<=300 &&c<=300)
          { while (l<=300 &&r<=300 &&c<=300)
            {back ();
            //Serial.print("7mra 5 hiright  ");
           break;}} 
            j=0;
            break;}  }
             else {
                 Serial.print("7mra 6666666  ");
                
                back ();
                delay (50);
                
                }}
 
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
   Serial.println(lfd);
   Serial.println(spd);
   Serial.println(spd0);


  
if(Serial.available()>0){ 
estado = Serial.read();
} 
Serial.println("bt " +estado);

if(estado=='L'){
 Max();
left ();

}

else if (estado=='R'){
  Max();
right ();
 
}
else if (estado=='G'){
  analogWrite(S1,spd);
  analogWrite(S2,255);
forward ();
 
}
else if (estado=='I'){
  analogWrite(S2,spd);
  analogWrite(S1,255);
forward ();
 
}
else if (estado=='H'){
  analogWrite(S1,spd);
  analogWrite(S2,255);
  back(); 
}
else if (estado=='J'){
  analogWrite(S2,spd);
  analogWrite(S1,255);
  back(); 
}
else if (estado=='1'){
 spd=25;
}
else if (estado=='2'){
 spd=50;
}
else if (estado=='3'){
 spd=75;
}
else if (estado=='4'){
 spd=100;
}
else if (estado=='5'){
 spd=125;
}
else if (estado=='6'){
 spd=150;
}
else if (estado=='7'){
 spd=175;
}
else if (estado=='8'){
 spd=200;
}
else if (estado=='9'){
 spd=225;
}
else if (estado=='q'){
 spd=255;
}
else if (estado=='W'){
 spd0=255;
}
else if (estado=='w'){
 spd0=210;
}
else if (estado=='U'){
 spd0=180;
}
else if (estado=='u'){
 spd0=150;
}
else if (estado=='X')
{
  lfd=800;
}
else if (estado=='x')
{
  lfd=500;
}
else if (estado=='v')
{
  
lfd=200;

  }

else if(estado=='F')
{
  Max();
forward ();

if (distance<=15)
 {

   
    while(timeElapsed<interval)
   {
  digitalWrite(13, HIGH);
 
 avoid();
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
  
else if (estado=='V')
{
  
lines ();

  }

// phase 3 orders

else if (estado=='z')
{
  right();
  delay(83.3*1.5);
  Stop();
}
else if (estado=='T')
{
  right();
  delay(125*1.4);
  Stop();
}
else if (estado=='Z')
{
  right();
  delay(166.6*1.3);
  Stop();
}
else if (estado=='c')
{
  right();
  delay(250*1.13);
  Stop();
}
else if (estado=='C')
{
  right();
  delay(500*.92);
  Stop();
}
else if (estado=='y')
{
  right();
  delay(750*.9);
  Stop();
}
else if (estado=='Y')
{
  right();
  delay(1000*0.83);
  Stop();
}

else if (estado=='m')
{
  forward();
  delay(58.8*1.45);
  Stop();
}

else if (estado=='M')
{
  forward();
  delay(117.64*1.12);
  Stop();
}

else if (estado=='l')
{
  forward();
  delay(588*1.1);
  Stop();
}

else if (estado=='Q')
{
  forward();
  delay(1176*1.12);
  Stop();
}

else if (estado=='e')
{
  forward();
  delay(2352*1.11);
  Stop();
}

else if (estado=='E')
{
  forward();
  delay(5880*1.11);
  Stop();
}

else if (estado=='t')
{
  forward();
  delay(11760*1.1);
  Stop();
}



else if (estado=='S')
{
/*   //rectangle
 
 d1=200; // width in cm
 d2=200 ;// length in cm
 t1=d1/90.0; // time for width
 t2=d2/90.0; //time for length
 for (i=0;i<2;i++)
 {
 analogWrite(S1,255); analogWrite(S2,255);
 forward();
 delay (t2*pow(10, 3));
 tanglerect1=((12.5/90.0)*((3*pi)/6)); // 12.5 is half of the distance between front and back of the carb in cm
  analogWrite(S1,255); analogWrite(S2,255);
  right();
  delay(tanglerect1*pow(10, 3));
  analogWrite(S1,255); analogWrite(S2,255);
  forward();
  delay (t1*pow(10, 3));
   tanglerect2=((12.5/90.0)*((3*pi)/5)); // 12.5 is half of the distance between front and back of the carb in cm
   analogWrite(S1,255); analogWrite(S2,255);
  right();
  delay(tanglerect2*pow(10, 3));}
  Stop ();
 delay(25000);*/

 for(int z=0 ;z<2;z++)
 {
   analogWrite(S1,255); analogWrite(S2,255);
  forward(); 
  delay(2352*1.11);
 Stop();
 delay(200);
 right();
 delay(250*1.13/2);
 forward(); 
  delay(2352*1.11);
  Stop();
  delay(200);
  right();
  delay(250*1.13/2);    
  if (z==1)
  {
    right();
    delay(125*1.4);
  }
 }
 Stop();
 delay(25000);

  analogWrite(S1,spd);
  analogWrite(S2,255);
forward ();

delay(5800);
 Stop();
 delay(25000);
 analogWrite(S2,spd-20);
  analogWrite(S1,255);
forward ();
delay(5800);
Stop();
delay (25000);
 analogWrite(S1,spd);
  analogWrite(S2,255);
forward ();

delay(5800);
Stop();
delay(500);
 analogWrite(S2,spd-20);
  analogWrite(S1,255);
forward ();
delay(5800);
}
 
 
 
// phase 3 finish

else 
{
  Stop();
  }
}
 
  
/*int tester ()
{
  f1=0;
  f2=0;
  f3=0;
  f4=0;
  f5=0;
  f6=0;
  ff=0;
  fff=0;
  if (l<lfd && c<lfd && r <lfd)
  {
    f1=1;
  }
  else
  {
    f1=0;
  }
  delay (50);
   if (l<lfd && c>lfd && r <lfd)
  {
    f2=1;
  }
   else
  {
    f2=0;
  }
  delay (50);
    if (l<lfd && c<lfd && r <lfd)
  {
    f3=1;
  }
   else
  {
    f3=0;
  }
   delay (50);
   if (l<lfd && c>lfd && r <lfd)
  {
    f4=1;
  }
   else
  {
    f4=0;
  }
  delay (50);
    if (l<lfd && c<lfd && r <lfd)
  {
    f5=1;
  }
   else
  {
    f5=0;
  }
  delay (50);
   if (l<lfd && c>lfd && r <lfd)
  {
    f6=1;
  }
   else
  {
    f6=0;
  }

  ff=f1+f2+f3+f4+f5+f6;
  
  if (ff>5)
  {
    fff=1;
  }
  else
  {
    fff=0;
  }

  return (fff);
}
*/
