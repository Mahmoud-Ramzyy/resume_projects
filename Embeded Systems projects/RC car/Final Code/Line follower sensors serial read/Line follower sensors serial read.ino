void setup() {
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("A3  ");
  Serial.println(analogRead(A3));
  Serial.print("A4  ");
  Serial.println(analogRead(A4));
  Serial.print("A5  ");
  Serial.println(analogRead(A5));


} 
