#include <elapsedMillis.h>
elapsedMillis timeElapsed;
unsigned int interval = 1500;
unsigned int interval2 = 750;
int i=0;        //actually i don't remember the using of it but it is important :v
int count=0;   //counter
int k;     //using as another counter 
int j;   //as a switcher in switch case
int led = 13;
int pin6=8;//B2
int pin7=9;//B1
int pin8=10;//A2
int pin9=11;//A1
const int trigPin = 3;
const int echoPin = 6;
int red=5;
int green=4;
int red_state;
int green_state;
float duration, distance;
char BluetoothData;


void setup() {
pinMode(led,OUTPUT);
pinMode(pin6,OUTPUT);
pinMode(pin7,OUTPUT);
pinMode(pin8,OUTPUT);
pinMode(pin9,OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(green, OUTPUT);
pinMode(red, OUTPUT);
Serial.begin(9600);
}


void loop() {

 



  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
   
   //timeElapsed=0;
    red_state=digitalRead(red);
    green_state=digitalRead(green);
    k=0;
       
 
    
    
    //this part of code is responsible on driving a car automaically without andorid app to avoid obstacles


//for (i=0;i<3;i++)

   switch (i<4) {
   TT: case 0:
      timeElapsed=0;
      break;
    case 1: if (j==0)
      timeElapsed=interval;
      else
     goto TT;
      break;
    /*   case 2:
      timeElapsed=2*interval;
      break;
        case 3:
      timeElapsed=3*interval;
      break;   */            //i predict we will need them later
     
    default:
     timeElapsed=0;
      break;
  }
   if ((distance>=0)&&(distance<40)) //55cm btw ultra sensor and barrier
  { 
    
   if ((distance>0) && (distance<=11))  //(stage 1)
    {digitalWrite(red,HIGH); 
    digitalWrite(green,HIGH);
    delay (100);
    digitalWrite(red,LOW); 
    digitalWrite(green,LOW);
      Serial.println("auto stop range 1");                         //detect with flashing
       Stop ();
      }
    else if ((distance>11) && (distance<=27.2)) //care about range from 11cm to 27.2cm ---->(stage 2)
    {digitalWrite(red,HIGH); //will detect with a red led
    digitalWrite(green,LOW);
            
         if (i<1)  
   { Serial.println("auto stop range 2"); 
     Stop ();
     i=1;}
     i=1;
   
     if (red_state==HIGH) {
      while (red_state==HIGH) 
      {
      Serial.println("auto back range 2"); 
       back ();
     break;
     }}
          //this loop will stay excuting as long as our detector (red led) is high
    }
     else if ((distance>27.2) && (distance<=40))  //another range from more than 27.2cm to 40cm ----->(stage 3)
     {
      timeElapsed=0; //to reset the timer to 0 before entering the loop
      digitalWrite(green,HIGH);   //here green led is the detector
    digitalWrite(red,LOW);
    for (count=0;count<1;count++){
  for (i=0;i<1;i++)
 {
   while (timeElapsed<interval) 
     {
      Serial.println("auto right range 3");
      Serial.println( "timeElapsed=");
      Serial.println( timeElapsed);
      right ();
     
     }
      i=2;
      }}
      
      
       //these 4 orders refering to turn right
         //this loop refering to the time required  to make car turn right completely -----> measured from video=1.5s
      
      
   Serial.println( "finally");
   timeElapsed=1500;
     
      Serial.println("auto stop range 3");
      Stop ();
     Serial.println( "timeElapsed3333=");
      Serial.println( timeElapsed);
  i=2;
  j=0;
   }
    
  
  }    else   if (distance>=40)   {
   
    digitalWrite(red,LOW); 
    digitalWrite(green,LOW);
    
   if ((count<1) && (timeElapsed>2)){
     Serial.println("auto stop range 5"); 
     Stop ();
     j=2;
   }
   
   for ( k=0;k<1;k++){
     if ((timeElapsed >= interval)&& (timeElapsed <= (interval+interval+interval))&&(count>=1))
     {
          digitalWrite(red,HIGH); 
          digitalWrite(green,HIGH); //acting like stage 3
        // for (i=0;i<1;i++)
         if (timeElapsed <= (interval+interval)&& (timeElapsed <= (interval+interval+interval))){
          Serial.println("auto stop range 5"); 
           Stop ();
          while (timeElapsed <= (interval+interval))
         {
           Serial.println("auto forward range 5.5"); 
           Serial.println( "timeElapsed 5.5=");
          Serial.println( timeElapsed);
          forward ();
        //  break;
         } 
         timeElapsed=3*interval;
         count=2;
         Serial.println( "timeElapsed=");
      Serial.println( timeElapsed);
          if (timeElapsed <= 4*interval){
            for (int j=0;j<1;j++){
          while (timeElapsed <= 4*interval)
          {
             Serial.println("auto left range 5.5"); 
             Serial.println( "the timeElapsed=");
             Serial.println( timeElapsed);
            left ();
            //timeElapsed=0;
            // break;
            }j=1;
            break;}
             
            }
          while (timeElapsed <= 4.5*interval)   //this condition will detect briefly in testing
            {
              forward ();
              Serial.println("auto forward range 6");
              Serial.println( "the timeElapsed=");
             Serial.println( timeElapsed);
               //goto AA;
            }


             
             AA: Serial.println("auto stop range 5.5"); 
             Stop ();
   
      Serial.println( "the fcin final timeElapsed=");
      Serial.println( timeElapsed);
     } 
     
   j=1;
    break; }
    else     {   if (Serial.available()){
      

BluetoothData=Serial.read();


if(BluetoothData=='L'){ 
left ();

}

else if (BluetoothData=='R'){
right ();
 
}
else if(BluetoothData=='F')
{
forward ();
}
else if (BluetoothData=='B')
{
back();
}

/* 
     the code of line follower sensor will add here isa








                

                                        */

                                                 
else
{
Stop ();
}}
    
    
       
    
    
    }  }  }       }
    // funcs for directions instead of orders to simplify the code
    void forward ()
    {Serial.println("forward");
     digitalWrite(pin6,HIGH);
     digitalWrite(pin7,LOW);
     digitalWrite(pin8,HIGH);
     digitalWrite(pin9,LOW);}
      void back ()
    {Serial.println("back");
     digitalWrite(pin6,LOW);
     digitalWrite(pin7,HIGH);
     digitalWrite(pin8,LOW);
     digitalWrite(pin9,HIGH);}
      void right ()
    {Serial.println("right");
     digitalWrite(pin6,HIGH);
     digitalWrite(pin7,LOW);
     digitalWrite(pin8,LOW);
     digitalWrite(pin9,HIGH);}
      void left ()
    {Serial.println("left");
     digitalWrite(pin6,LOW);
     digitalWrite(pin7,HIGH);
     digitalWrite(pin8,HIGH);
     digitalWrite(pin9,LOW);}
      void Stop ()                //care to 's' char in stop ----> capital
    {Serial.println("stop");
     digitalWrite(pin6,LOW);
     digitalWrite(pin7,LOW);
     digitalWrite(pin8,LOW);
     digitalWrite(pin9,LOW);}




