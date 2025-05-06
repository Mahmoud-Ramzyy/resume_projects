//motor A

#define in1 8
#define in2 9
//motor b

#define in3 10
#define in4 11

const int trigPin = 3;
const int echoPin = 6;

long duration;
int distance;
char estado ;
void setup() {
Serial.begin(9600);
 pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}
void loop() {
// Clears the trigPin
AA:digitalWrite(trigPin, LOW);
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



  
if(Serial.available()>0){ 
estado = Serial.read();
} 

if(estado=='F')
 { Serial.println(estado); 

digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

if(estado=='B'){ 
    Serial.println(estado);
   
  digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }

    
if(estado=='R'){  
    Serial.println(estado);  

 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
}
if(estado=='L'){ 
    Serial.println(estado); 
 digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
if(estado=='S'){ 
    Serial.println(estado);
  digitalWrite(in1,LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);
}

 for ( int i=0; distance<=18;i++)
 { digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay (800);
  digitalWrite(in1, LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4,LOW);
  goto AA;
  }
} 
  
  




