const int trigPin = 9;
const int echoPin = 10;
int red=11;
int green=12;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
  if (distance<500)
  { digitalWrite(red, HIGH);
   digitalWrite(green, LOW);}
   else
   { digitalWrite(green, HIGH);
    digitalWrite(red, LOW);}
  
}
