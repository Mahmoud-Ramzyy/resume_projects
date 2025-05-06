# define  left_sen A3   
# define  center_sen A4 
#define right_sen A5 

//motor A
//right motor
#define in1 8
#define in2 9
//motor b
//left motor

#define in3 10
#define in4 11
int lineStandard = 800;



void setup()
{ pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
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


  
  if(analogRead( center_sen) > lineStandard)
  {
 forward ();
  }
 
  else if(analogRead(right_sen) > lineStandard)
  {//right
 right();
  }
  //data_sheet
  // if the line is under the left sensor, adjust relative speeds to turn to the left
  else if(analogRead(left_sen) > lineStandard)
  {//left
 left();
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

