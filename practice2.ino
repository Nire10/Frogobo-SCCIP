#include <Servo.h>

int lightLeft = 0;
int lightMid = 1;
int lightRight = 2;
const int motorLeft = 6;
const int motorRight = 5;
const int magPin = 3;
Servo servo1;
int positionx = 170;

void setup() {
  Serial.begin(9800); //for debugging
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  servo1.attach(7);
  servo1.write(positionx);
}

void loop() {
  int Speed1 = 150;
  int Speed2 = 150;
  int magFound = 0;
  int lightLevelMid = analogRead(lightMid);
  int lightLevelRight = analogRead(lightRight);
  int lightLevelLeft = analogRead(lightLeft) + 10;
  analogWrite(motorLeft, Speed1);
  analogWrite(motorRight, Speed1);
  delay(300);
 
while(magFound <= 900)  //Keeps followling light until it finds the magnet
{
  lightLevelMid = analogRead(lightMid);
  lightLevelRight = analogRead(lightRight) + 10;
  lightLevelLeft = analogRead(lightLeft) + 10;

  if (lightLevelMid > lightLevelRight && lightLevelMid > lightLevelLeft)
    {
      //Serial.println("Straight");
      analogWrite(motorLeft, Speed1);
      analogWrite(motorRight, Speed1);
    }
  else 
    {  
      if (lightLevelLeft < lightLevelRight)
      //Serial.println("Right");
      {
      analogWrite(motorLeft, Speed2);
      analogWrite(motorRight, 50); 
      }
      
      else
      {
      //Serial.println("Left");   
      analogWrite(motorRight, Speed2);
      analogWrite(motorLeft, 50);
      }  
    }  
 
  magFound = analogRead(magPin);
  //delay(10);
}

 analogWrite(motorRight, 0);  //pause
 analogWrite(motorLeft, 0);
 delay(500);

 //turn around
 analogWrite(motorLeft, Speed1); 
 delay(2800);
 analogWrite(motorLeft, 0);
 delay(20);
 
 analogWrite(motorLeft, Speed1);
 analogWrite(motorRight, Speed1);
 delay(300);
 analogWrite(motorLeft, 0);
 analogWrite(motorRight, 0);
 delay(20);
 
 analogWrite(motorRight, Speed1);
 delay(400);

 analogWrite(motorRight, 0);  //pause
 analogWrite(motorLeft, 0);
 delay(500);
 
 do  //go back, follow until end of light
  {
    lightLevelMid = analogRead(lightMid);
    lightLevelRight = analogRead(lightRight) + 10;
    lightLevelLeft = analogRead(lightLeft) + 10;
    
    if (lightLevelMid > lightLevelRight && lightLevelMid > lightLevelLeft)
    {
      //Serial.println("Straight");
      analogWrite(motorLeft, Speed1);
      analogWrite(motorRight, Speed1);
    }
    else 
    {  
      if (lightLevelLeft < lightLevelRight)
      //Serial.println("Right");
      { 
      analogWrite(motorLeft, Speed2);
      analogWrite(motorRight, 50); 
      }
      
      else
      {
      //Serial.println("Left");   
      analogWrite(motorRight, Speed2);
      analogWrite(motorLeft, 50);
      }  
    }  
 
  }while (lightLevelMid > 900 || lightLevelRight > 800 || lightLevelLeft > 800);

  analogWrite(motorRight, Speed1);
  analogWrite(motorLeft, Speed1);
  delay(100);
  analogWrite(motorRight, 0);
  analogWrite(motorLeft, 0);
   
   for(positionx = 170; positionx > 30; positionx -= 2) //spit out stick with magnet
  {
    servo1.write(positionx); 
    delay(20);             
  } 

  servo1.write(170);

  delay(10000);
  
}

