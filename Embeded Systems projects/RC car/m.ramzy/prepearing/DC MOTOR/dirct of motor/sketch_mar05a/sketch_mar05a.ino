void setup() {
  pinMode(11,OUTPUT); //for direct to right
  pinMode(10,OUTPUT); //for direct to left
}

void loop() {
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  delay(3000);
  digitalWrite(10,HIGH);
   digitalWrite(11,LOW);
  delay(3000);

}
