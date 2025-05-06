
const int LED=13;
const int sensor=A0;
int sensorval;
void setup() {
  pinMode(LED,OUTPUT);
  // put your setup code here, to run once:

}

void loop() { sensorval=analogRead(sensor);
  digitalWrite(LED,HIGH);
  delay(sensorval);
  digitalWrite(LED,LOW);
  delay(sensorval);
  // put your main code here, to run repeatedly:

}
