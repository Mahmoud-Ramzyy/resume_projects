//example01
const int LED=12;
const int button=2;
int val;
void setup() {
  pinMode(LED,OUTPUT);
  pinMode(button,INPUT);
  // put your setup code here, to run once:

}

void loop() { val=digitalRead(button);
if(val==HIGH){
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(500);}
  else{digitalWrite(LED,LOW)}
  // put your main code here, to run repeatedly:

}
