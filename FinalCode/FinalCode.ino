#include <EYW.h>
#include <Servo.h>
#include <Wire.h>

/******************************* CREATE VARIABLES ********************************/

Servo myservo;           // create servo object to control the camera servo
EYW::RangeFinder sonic;  // object used to read from the ultrasonic range finder

int buzzerP  = 0;        // pin used for the piezo speaker
int buttonP  = 0;        // pin used to read from the button
int ledP     = 0;        // pin used to control the led

int angleMax = 90;       // maximum position for the servo to turn 
int angleMin = 0;        // position for the serco to return to
int degree   = angleMin; // variable used to store the position of the servo

/******************************** CREATE METHODS *********************************/

void init()              // set up all values for use in the program
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);
  
}

void calibration()       // used for the 
{
  
}

void takePicture()       // turns the motor to the max then returns it to the min
{
  for(; val<=90; v++){
    myservo.write();
    delay(15);
  }
  delay(50);
  for(; val>=0; v--){
    myservo.write();
    delay(15);
  }
}

/****************************** DEFAULT RUN METHODS ******************************/

void setup() 
{

  init();
  
}

void loop() 
{
    
  float distance = getDistance();
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else if(distance >= 12 || distance <= 10) {
    val = 20;            
    myservo.write(val);
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    val = 0;
    myservo.write(val);  
    delay(500);
  }
  delay(500);
}

