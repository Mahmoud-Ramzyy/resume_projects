//motor A 
8 
 
9 #define in1 8 
10 #define in2 9 
11 
 
12 //motor b 
13 
 
14 #define in3 10 
15 #define in4 11 
16 
 
17 
 
18 int r, c, l ; 
19 const int trigPin = 2; 
20 const int echoPin = 6; 
21 int led = 13; 
22 int h=2; 
23 int b=2; 
24 int S1=5 , S2=3; //Capital S 
25 long duration; 
26 int distance; 
27 char estado ; 
28 int spd=255; 
29 int spd0=180; 
30 int lfd=400; 
31 int f1,f2,f3,f4,f5,f6,ff,fff; 
32 unsigned int interval = 1000; 
33   elapsedMillis timeElapsed; 
float tcircle;omega;r3;r2;r1;v1;v2;N1;N2;d1;d2;t1;t2;pi;d;t
int i;
pi=3.14;
34 void setup() { 
35 Serial.begin(9600); 
36 pinMode(S1,OUTPUT); 
37 pinMode(S2,OUTPUT); 
38 pinMode(A3,INPUT); 
39   pinMode(A4,INPUT); 
40   pinMode(A5,INPUT); 
41  pinMode(in1, OUTPUT); 
42   pinMode(in2, OUTPUT); 
43   pinMode(in3, OUTPUT); 
44   pinMode(in4, OUTPUT); 
45   pinMode(led, OUTPUT); 
46 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output 
47 pinMode(echoPin, INPUT); // Sets the echoPin as an Input 
48 
 
49 } 
50 void loop() { 
51 // Clears the trigPin 
52 digitalWrite(trigPin, LOW); 
53 delayMicroseconds(2); 
54 // Sets the trigPin on HIGH state for 10 micro seconds 
55 digitalWrite(trigPin, HIGH); 
56 delayMicroseconds(10); 
57 digitalWrite(trigPin, LOW); 
58 // Reads the echoPin, returns the sound wave travel time in microseconds 
59 duration = pulseIn(echoPin, HIGH); 
60 // Calculating the distance 
61 distance= duration*0.034/2; 
62 // Prints the distance on the Serial Monitor 
63 Serial.print("Distance: "); 
64 Serial.println(distance); 
65 digitalWrite(led,LOW); 
66 l=analogRead(A3); 
67 c=1000-analogRead(A4); 
68 r=analogRead(A5); 
69  Serial.print("l  "); 
70     Serial.println(analogRead(A3)); 
71   Serial.print("c  "); 
72   Serial.println(1000-analogRead(A4)); 
73   Serial.print("r  "); 
74   Serial.println(analogRead(A5)); 
75    Serial.println(lfd); 
76    Serial.println(spd); 
77    Serial.println(spd0); 
78 
 
79 
 
80    
81 if(Serial.available()>0){  
82 estado = Serial.read(); 
83 }  
84 Serial.println("bt " +estado); 
85 if(estado=='L'){ 
86  Max(); 
87 left (); 
88 
 
89 } 
90 
 
91 else if (estado=='R'){ 
92   Max(); 
93 right (); 
94   
95 } 
96 else if (estado=='G'){ 
97   analogWrite(S1,100); 
98   analogWrite(S2,255); 
99 forward (); 
100   
101 } 
102 else if (estado=='I'){ 
103   analogWrite(S2,100); 
104   analogWrite(S1,255); 
105 forward (); 
106   
107 } 
108 else if (estado=='H'){ 
109   analogWrite(S1,100); 
110   analogWrite(S2,255); 
111   back();  
112 } 
113 else if (estado=='J'){ 
114   analogWrite(S2,100); 
115   analogWrite(S1,255); 
116   back();  
117 } 
118 else if (estado=='1'){ 
119  spd=25; 
120 } 
121 else if (estado=='2'){ 
122  spd=50; 
123 } 
124 else if (estado=='3'){ 
125  spd=75; 
126 } 
127 else if (estado=='4'){ 
128  spd=100; 
129 } 
130 else if (estado=='5'){ 
131  spd=125; 
132 } 
133 else if (estado=='6'){ 
134  spd=150; 
135 } 
136 else if (estado=='7'){ 
137  spd=175; 
138 } 
139 else if (estado=='8'){ 
140  spd=200; 
141 } 
142 else if (estado=='9'){ 
143  spd=225; 
144 } 
145 else if (estado=='q'){ 
146  spd=255; 
147 } 

151 else if (estado=='w'){ 
152  spd0=210; 
153 } 
154 else if (estado=='U'){ 
155  spd0=180; 
156 } 
157 else if (estado=='u'){ 
158  spd0=150; 
159 } 
160 else if (estado=='X') 
161 { 
162   lfd=800; 
163 } 
164 else if (estado=='x') 
165 { 
166   lfd=500; 
167 } 
168 
 
169 else if(estado=='F') 
170 { 
171   Max(); 
172 forward (); 
173 
 
174 if (distance<=15) 
175  { 
176 
 
177     
178     while(timeElapsed<interval) 
179    { 
180   digitalWrite(13, HIGH); 
181   
182  avoid(); 
183    } 
184    timeElapsed=0; 
185     digitalWrite(led,LOW); 
186  Stop(); 
187    
188    
189 
 
190   } 
191 } 
192 else if (estado=='B') 
193 { 
194   Max(); 
195 back(); 
196 } 
197 
 
198 else if (estado=='V') 
199 { 
200    
201 lf (); 
202 
 
203   } 
204 else if (estado=='v') 
205 { 
206    
207 lfd=200; 
208 Stop(); 
209 
 
210   } 
211 else  
212 { 
213   Stop(); 
214   } 
215 
216   
217    
218    
219 void Max() 
220 { 
221   analogWrite(S1,spd); 
222   analogWrite(S2,spd); 
223   } 
224 
 
225   void forward () 
226     { 
227      
228      digitalWrite(in1, HIGH); 
229   digitalWrite(in2, LOW); 
230   digitalWrite(in3, HIGH); 
231   digitalWrite(in4, LOW);} 
232       void back () 
233     { 
234       
235       digitalWrite(in1, LOW); 
236   digitalWrite(in2,HIGH); 
237   digitalWrite(in3, LOW); 
238   digitalWrite(in4, HIGH);} 
239       void right () 
240     { 
241        
242       digitalWrite(in1, HIGH); 
243  digitalWrite(in2, LOW); 
244  digitalWrite(in3, LOW); 
245  digitalWrite(in4, HIGH);} 
246 
 
247   
248       void left () 
249  { 
250 
 
251      digitalWrite(in1, LOW); 
252   digitalWrite(in2, HIGH); 
253   digitalWrite(in3, HIGH); 
254   digitalWrite(in4, LOW);} 
255 
 
256    
257       void Stop ()                //care to 's' char in stop ----> capital 
258 { 
259      digitalWrite(in1, LOW); 
260   digitalWrite(in2, LOW); 
261   digitalWrite(in3, LOW); 
262   digitalWrite(in4, LOW);} 
263 
 
264   void avoid() 
265   { 
266      back(); 
267       delay(500); 
268   right(); 
269     delay(300); 
270     if (distance <20) 
271     { 
272       Stop(); 
273     } 
274      else { 
275    forward(); 
276     delay(1000); 
277     left(); 
278    delay(300);  
279       Stop(); 
280    /*    forward(); 
281    delay(1000); 
282     left(); 
283     delay(300);  
284      
285     forward(); 
286     delay(500); 
287     right(); 
288     delay(300); 
289     Stop();*/ 
290     } 
291     } 
292      
293 
 
294   
295  void lf () 
296    { 
297       if((c > lfd && r < lfd && l < lfd )|| (c > lfd && r> lfd && l > lfd)) 
298   { 
299     
300   
301       analogWrite(S1,spd); analogWrite(S2,spd); 
302   h=1; 
303     
304     forward(); 
305      Serial.println("FFFFFF"); 
306   } 
307  else if((r >lfd && c < lfd && l < lfd)||(r >lfd && c > lfd && l < lfd)) 
308   { 
309    analogWrite(S1,spd0); analogWrite(S2,spd0); 
310   h=2; 
311   b=2; 
312    right(); 
313  Serial.println("RRRRRRRR"); 
314      
315   } 
316    
317 
 
318   else if((l > lfd && c<lfd && r <lfd)||(l > lfd && c>lfd && r <lfd)) 
319   { 
320    analogWrite(S1,spd0); analogWrite(S2,spd0); 
321    h=3; 
322    b=3; 
323   left(); 
324    
325     Serial.println("LLLLLLLLLLL"); 
326    } 
327    
328  else  
329   { 
330     if (h==1) 
331     {  analogWrite(S1,spd0); analogWrite(S2,spd0);  
332 
 
333     right(); 
334     /* if (b==2) 
335      { 
336      left(); 
337      
338    } 
339    else if (b==3) 
340    { 
341     right(); 
342    }*/ 
343      Serial.println("EEEEEEE1111111"); 
344      } 
345      
346     if (h==2) 
347     {  analogWrite(S1,spd0); analogWrite(S2,spd0); 
348 
 
349    
350    right(); 
351    Serial.println("EEEEEEEEEE222222222"); 
352     } 
353     if (h==3) 
354     {   
355        
356       analogWrite(S1,spd0); analogWrite(S2,spd0);  
357       left(); 
358       Serial.println("EEEEEEEE3333333333"); 
359       } 
360       
361 } 
362 
 
363 } 
364    
365 /*int tester () 
366 { 
367   f1=0; 
368   f2=0; 
369   f3=0; 
370   f4=0; 
371   f5=0; 
372   f6=0; 
373   ff=0; 
374   fff=0; 
375   if (l<lfd && c<lfd && r <lfd) 
376   { 
377     f1=1; 
378   } 
379   else 
380   { 
381     f1=0; 
382   } 
383   delay (50); 
384    if (l<lfd && c>lfd && r <lfd) 
385   { 
386     f2=1; 
387   } 
388    else 
389   { 
390     f2=0; 
391   } 
392   delay (50); 
393     if (l<lfd && c<lfd && r <lfd) 
394   { 
395     f3=1; 
396   } 
397    else 
398   { 
399     f3=0; 
400   } 
401    delay (50); 
402    if (l<lfd && c>lfd && r <lfd) 
403   { 
404     f4=1; 
405   } 
406    else 
407   { 
408     f4=0; 
409   } 
410   delay (50); 
411     if (l<lfd && c<lfd && r <lfd) 
412   { 
413     f5=1; 
414   } 
415    else 
416   { 
417     f5=0; 
418   } 
419   delay (50); 
420    if (l<lfd && c>lfd && r <lfd) 
421   { 
422     f6=1; 
423   } 
424    else 
425   { 
426     f6=0; 
427   } 
428  
429   ff=f1+f2+f3+f4+f5+f6; 
430    
431   if (ff>5) 
432   { 
433     fff=1; 
434   } 
435   else 
436   { 
437     fff=0; 
438   } 
439  
440   return (fff); 
441 } 
442 */ 



  if (estado=='1'){ 
  shapes();
   } 
  void shapes()
  {
    
 //rectangle
 
 d1=100 // width in cm
 d2=400 // length in cm
 t1=d1/90.0 // time for width
 t2=d2/90.0 //time for length
 for (i=0;i<2;i++)
 {
 analogWrite(S1,255); analogWrite(S2,255);
 forward();
 delay (t2*pow(10, 3));
 tanglerect=((12.5/90.0)*(pi/2)); // 12.5 is half of the distance between front and back of the carb in cm
  analogWrite(S1,255); analogWrite(S2,255);
  right();
  delay(tanglerect*pow(10, 3));
  analogWrite(S1,255); analogWrite(S2,255);
  forward();
  delay (t1*pow(10, 3));
   tanglerect=((12.5/90.0)*(pi/2)); // 12.5 is half of the distance between front and back of the carb in cm
   analogWrite(S1,255); analogWrite(S2,255);
  right();
  delay(tanglerect*pow(10, 3));}
   stop();
 delay(25000);
 //circle
    tcircle=12.0;
  omega=(2*pi)/tcircle;
  r3=100.0; //circle radius of thecar body in cm
  r1=r3-6.5; // circle radius of the car`s right wheel in cm and 6.5is  half of the distance between the two wheels in cm
  r2=r1+13.0;// circle radius of the car`s left wheel in cm and 13 is distance between the two wheels in cm
 v1=omega*r1;// right wheel
 v2=omega*r2;// left wheel
 N1=(V1*255)/90.0 //N1=s2 // right wheel
 N2=(v2*255)/90.0 //N2=s1 // left wheel
 analogWrite(S1,N2); analogWrite(S2,N1);
 forward();
 delay(tcircle*pow(10, 3));
 stop();
 delay(25000);
 
  
  } 
   if (estado==2){
 angle();}
 
 void angle(){
  theta=pi/6
  tangle=((12.5/90.0)*theta)
  right();
  delay(tangle*pow(10, 3));
 }
  if (estado==3){
distane();}
void distance(){
  d=40
  t=d/90.0 
  analogWrite(S1,255); analogWrite(S2,255);
 forward();
 delay (t*pow(10, 3));
}

 
 
  }


