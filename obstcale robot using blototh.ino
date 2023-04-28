/**************************************************************************************************
 Name        : Mohamed Refaat Abdelazim
 Description : C Program for Bluetooth Controlled Obstacle Avoiding Arduino Robotic Car
               This robot controlled by Bluetooth with the help of Android App. 
               It also senses obstacles and stop to avoid collision.
**************************************************************************************************/

#include<Servo.h>
#include<string.h>
Servo m; 
const int trigPin =2 ;
const int echoPin = 3;
char z;
bool f = 0 ;
bool r = 0 ;
bool l = 0 ;
bool b = 0 ;
bool s = 0 ;
long duration;
int distance,cdistance,rdistance,ldistance;
int in1 =5;  //Right motor pole 1
int in2 =6 ; //Right motor pole 2
int in3=7;//left motor pole 1
int in4=8;  //left motor pole 1
void setup() {
  Serial.begin(9600);
  m.attach(4);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
     m.write(90);
}

void loop() { 
  while (Serial.available() > 0)
  {
    z=Serial.read();
    Serial.println(z);
if(z =='F')
{
  f = 1;
  r = 0 ;
 l = 0 ;
 b = 0 ;
 s = 0 ;
  
}
else if (z =='S')
{
 f = 0 ;
 r = 0 ;
 l = 0 ;
 b = 0 ;
 s = 1;
}
else if (z =='R'){
  f=0 ;
  r=1 ;
  l=0 ;
  b=0 ;
  s = 0;
}
else if (z =='L'){
 f=0 ;
  r=0 ;
  l=1 ;
  b=0 ;
  s = 0;
  }
  else if (z=='G')
  {
  f=0 ;
  r=0 ;
  l=0 ;
  b=1 ;
  s = 0;
}
  }
 if(f == 1){
  forward();  
}
else if (r == 1){
right();
}
else if (l == 1){
 left();
  }
  else if (b == 1){
  backward();
  }
  else if(b&&r&&f&&l == 0){
  stopy();
  }
  else if (s == 1){
    stopy();
  }
  /*


cdistance=ultrasonic();
if(cdistance>16)
forward();
else if(cdistance<=16)
{
stopx();
servox();
if(rdistance>ldistance){
right();
delay(500);
}
else{
left();
delay(500);
}
}*/

  }

 void servox(){
  
       for(int x = 90; x <= 180; x++)  
  {                                  
    m.write(x);               
    delay(3); 
    if(x==180){
      delay(500);
      ldistance=ultrasonic();
      }                
  } 
     for(int x = 180; x >= 0; x--)  
  {                                  
    m.write(x); 
      if(x==0){
      delay(500);
      rdistance=ultrasonic();
      }                          
    delay(3);                 
  } 
    for(int x = 0; x <= 90; x++)  
  {                                  
    m.write(x);               
    delay(3);                 
  } 
  }
  int ultrasonic(void)
{
  distance=0;
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
return distance;
}
void backward(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void forward(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void  left(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void right(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void stopx(){
   digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(110);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void stopy(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
