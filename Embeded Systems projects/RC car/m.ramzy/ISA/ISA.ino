#define in1 8
#define in2 9
#define in3 10
#define in4 11

int r=A5, c=A4, l=A3 ;
int led = 13;
int S1=5 , S2=3; //Capital S
//int ref=500;
int j=1;  //switcher
void setup() {
Serial.begin(9600);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);}
void loop () {
   Serial.print("\n");
   Serial.print(" l  ");
    Serial.println(analogRead(A3));
  Serial.print("c  ");
  Serial.println(1024-analogRead(A4));
  Serial.print("r  ");
  Serial.println(analogRead(A5));
  r=analogRead(A5);
  c=1024-analogRead(A4);
  l=analogRead(A3) ;
    
    
  line ();
             
       
  
  
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
    void left2 ()
 {
  analogWrite(S2,100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);}

    void left3 ()
 {
  analogWrite(S2,100);
  analogWrite(S1,80);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);}
 void line ()
 { if (c>300 &&r<=300 &&l<=300 ||c>300 &&l<=300 &&r>300 ||c>300 &&r<=300 &&l>300)
  {while (c>300 &&r<=300 &&l<=300 ||c>300 &&l<=300 &&r>300 ||c>300 &&r<=300 &&l>300)
   { 
    
    forward ();
    Serial.print("7mra 1 11111 ");
    break;
    }}
       else if (c<=300 &&r<=300 &&l>300)
       {while (c<=300 &&r<=300 &&l>300)
        {  
           Serial.print("7mra 222222  ");
          j=1;
        /*   if (c<=300)
           { while (c<=300)
             { Serial.print("7mra 2.111111  ");
              forward();
             break;}} */
              if (l>300 && c<=300)
           {  while (l>300 &&c<=300)
             { Serial.print("7mra 2.....222222  ");
              right ();
             break;
              }}
              
             
               break;}}
              else if ( c<=300 &&l<=300 &&r>300)
               {while  (c<=300 &&l<=300 &&r>300)
               { 
          j=2;
          Serial.print("7mra 333333  ");
        /*  if (c<=300)
            {while (c<=300)
             {Serial.print("7mra 3.1111  ");
              forward();
             break;}} */
             if (r>300 &&c<=300)
            { while (r>300 &&c<=300)
             {
              Serial.print("7mra 3.22222  ");
              left ();
             break;
              }}
        
              break;}}
          else  if (c>300 &&r>300 &&l>300)
               {while(c>300 &&r>300 &&l>300)
        
                
      {  
            if (r>300 &&l>300)
            { while (r>300 &&l>300)
              {forward ();
              break;}}
               Serial.print("7mra 44444444  ");
          
            break;}
               }
        
      else  if (c<=300 &&r<=300 &&l<=300) 
            { while (c<=300 &&r<=300 &&l<=300)
             { 
        
           Serial.print("7mra 55555  ");
           if (l<=300&&j==1)
           {while (l<=300)
          { left ();
           Serial.print("7mra 5 hileft  ");
          break;}}
           if (j==2&&r<=300)
          { while (r<=300)
            {right ();
           Serial.print("7mra 5 hiright  ");
           break;}} 
            j=1;
            break;}  }
             else {
                 Serial.print("7mra 6666666  ");
                
                back ();
                delay (50);
                
                }}
