int y = 5;
int g = 2;
int r = 4;
int x=0;
void setup() {
  
pinMode(r,OUTPUT);
pinMode(y,OUTPUT);
pinMode(g,OUTPUT);
}

void loop() {
  digitalWrite(r,HIGH);
  delay(4000);
   digitalWrite(r,LOW);
  delay(200);
  for(x = 0;x<4;x++) {digitalWrite(y,HIGH);
  delay(500);
   digitalWrite(y,LOW);
  delay(500);
    }
    x=0;
    digitalWrite(g,HIGH);
  delay(7000);
   digitalWrite(g,LOW);
  delay(200);
  
    
     digitalWrite(y,HIGH);
  delay(3000);
   digitalWrite(y,LOW);
  delay(200);
  
  
  

}
