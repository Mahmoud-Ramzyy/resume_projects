# define  left_sen 2
# define  center_sen 13
#define right_sen 7

//motor A
//right motor
#define in1 8
#define in2 9
//motor b
//left motor

#define in3 10
#define in4 11
int lineStandard =127;



void setup()
{ pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(7, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  
Serial.begin(9600);
 Serial.println("IR Sensor Readings:: ");
 delay(1000);
}

void loop()
{
  Serial.print( analogRead(left_sen));
  Serial.print("\t");  
  Serial.print(analogRead( center_sen));
  Serial.print("\t"); 
  Serial.print(analogRead(right_sen));
  Serial.println();


  
  for(int i=0;(center_sen) ==LOW &&digitalRead(right_sen)==HIGH && digitalRead(left_sen)==HIGH;i++)
  {
  forward();
  delay (200);
  }
 
  for(int i=0;digitalRead( center_sen) ==HIGH &&digitalRead(right_sen)==LOW && digitalRead(left_sen)==HIGH;i++)
  {
 right (); delay (200);
  }
 for(int i=0;digitalRead( center_sen) ==HIGH &&digitalRead(right_sen)==HIGH && digitalRead(left_sen)==LOW;i++)
  {
 left (); delay (200);
  }
  for(int i=0 ;digitalRead( center_sen) ==LOW &&digitalRead(right_sen)==LOW && digitalRead(left_sen)==HIGH;i++)
  {
 right (); delay (200);
  }
 
  for(int i=0;digitalRead( center_sen) ==LOW &&digitalRead(right_sen)==HIGH && digitalRead(left_sen)==LOW;i++)
  {
 left (); delay (200);
  }
  for(int i=0;digitalRead( center_sen) ==HIGH &&digitalRead(right_sen)==HIGH && digitalRead(left_sen)==HIGH;i++)
  {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  }
  
  

 

  
  
 
  delay(0);  // add a delay to decrease sensitivity.
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right() {
 digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


