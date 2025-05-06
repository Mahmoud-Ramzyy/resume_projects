int mot=10;
int pot=A0;
int sp;
void setup() {
  

}

void loop() {
sp=analogRead(pot)/4;
analogWrite(mot,sp);
}
