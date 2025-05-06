int led = 13;
int pin6=8;//B2
int pin7=9;//B1
int pin8=10;//A2
int pin9=11;//A1
char BluetoothData;
void setup() {

pinMode(pin6,OUTPUT);
pinMode(pin7,OUTPUT);
pinMode(pin8,OUTPUT);
pinMode(pin9,OUTPUT);

Serial.begin(9600);
}
void loop() {



digitalWrite(pin6,LOW);
digitalWrite(pin7,HIGH);
digitalWrite(pin8,HIGH);
digitalWrite(pin9,LOW);

}

