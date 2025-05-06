
int led=13;  // motor is connected to the analog pin 10 of arduino

String trans;



void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
  Serial.println("Please enter 'w' for running,'s' for stop ");
  while(Serial.available()==0){   }
  
  trans=Serial.readString();
  if(trans=="w"){
  digitalWrite(led,HIGH);
  delay(500);
  }

  if(trans=="s"){
  digitalWrite(led,LOW);
  delay(500);
  }
}
