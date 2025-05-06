int dir1=13;
int dir2=12;
int sp=11;
int sw=2; //for switch
int pot=A0;
int cont; //THE VALUE OF speed control from pot
void setup() {
 pinMode(dir1,OUTPUT);
 pinMode(dir2,OUTPUT);
 pinMode(sw,INPUT);
}

void loop() {
  cont=analogRead(pot)/4;
  analogWrite(sp,cont);
  if (digitalRead(sw)==HIGH)
  {digitalWrite(dir1,HIGH);
   digitalWrite(dir2,LOW);
   delay(1500);}
   else {
   digitalWrite(dir2,HIGH);
   digitalWrite(dir1,LOW);
   delay(1500);
   }

}
