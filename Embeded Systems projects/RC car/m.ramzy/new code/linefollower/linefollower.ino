#define in1 8
#define in2 9
#define in3 10
#define in4 11
int r=analogRead(A5), c=1000-analogRead(A4), l=analogRead(A3) ;
const int trigPin = 2;
const int echoPin = 6;
char BluetoothData ;
int S1=5 , S2=3; //Capital S
int ref=200;
long duration;
int distance;

void setup() {
Serial.begin(9600);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
  
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}
void loop (){
   // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

   
   if (c>ref &&r<=ref &&l<=ref)
   {
    tt: forward();
        delay (80);
        if (c>ref && l<=ref)
            forward ();
          else
          goto uu;   
             }
        else if (c>ref &&r<ref &&l>ref)
       {
        uu:if (r<=ref &&l>ref)
            {while (r<=ref &&l>ref)
             {right2();
              break;} } 
            goto tt;}
       else if (c>ref &&r>ref &&l>ref)
       {
        ii: if (r>ref &&l>ref)
             {while (r>ref &&l>ref)
              {right2 ();
               break;} }
              goto uu;} 
        else if (c>ref &&r>ref &&l<=ref) 
        {
         yy:  if (r>ref &&l<ref) 
              {while (l<=ref)
              { right2 ();
               break;}}
               goto ii;}
         else if (c<=ref &&r<=ref &&l>ref)  
          { if (c<=ref &&l>ref)
              {while (c<=ref)
                {forward ();
                 break;}}
                 goto uu;}
          else if (c<=ref &&l<=ref &&r>ref) 
           {   if (l<=ref &&r>ref)
                 {while (l<=ref)
                   {right2 ();
                   break;}}
                   goto ii;} 
            else 
              easydrive ();            
            
  }           
    void forward ()
  {
    
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);}
      void back ()
  {
     
  digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);}
     void right ()
  {
      
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);}

 
      void left ()
 {

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);}

  
      void Stop ()                //care to 's' char in stop ----> capital
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);}
     void right2 () 
 
 {
 analogWrite(S1,100);
  
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);}  
void avoid (){
  back();
  delay(500);
  right();
  delay(300); 
   if (distance <18)
    {delay(500);
     right();
     delay(300); }
    else { forward();
   delay(1000);
    left();
    delay(500);
    Stop ();
    }
  }
   void easydrive () { 
   if (distance <18) 
   avoid ();   
     
  else {  
if (Serial.available()>0){
      

BluetoothData=Serial.read();


if(BluetoothData=='L'){ 
left ();

}

else if (BluetoothData=='R'){
right ();
 
}
else if(BluetoothData=='F')
{
forward ();
}
else if (BluetoothData=='B')
{
back();
}}}
 
   }
