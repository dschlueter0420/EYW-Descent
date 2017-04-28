/*
  Descent Program
  
  This program is used in conjunction with a parachuting system that takes pictures while descending
  
  Program Flow:
  * Initialize variables and objects
  * Waits for user to press button
  * Alerts user of calibration start
  * Calibrates sensors
  * Alerts user of calibration stop
  * Begins main function loop
  * Checks if target alititude is reached
    - Too low is signalled by one alert
    - Too high is signalled by two alerts
    - Correct altitude is signalled by five alerts
  * Start taking pictures
  * If height is less than one meter
    - Stop taking pictures
    - Alert the user every 3 seconds
  
  Circuit:
  * (To be added)
  
  Created   28 Apr 2017
  Modified  29 Apr 2017
  
  For Team 6-A
  By  David Schlueter

*/

/******************************* IMPORT LIBRARIES ********************************/

#include <EYW.h>
#include <Servo.h>
#include <Wire.h>

/******************************* CREATE VARIABLES ********************************/

Servo myservo;           // create servo object to control the camera servo
EYW::RangeFinder sonic;  // object used to read from the ultrasonic range finder (in cm)
EYW::Altimeter   altim;  // object used to read from the altimeter (in m)

boolean hReached;        // stores if the starting altitude been reached

int hTarget  = 25;       // the target starting height (in m)

int buzzerP  = 0;        // pin used for the piezo speaker
int buttonP  = 0;        // pin used to read from the button
int ledP     = 0;        // pin used to control the led

int angleMax = 90;       // maximum position for the servo to turn 
int angleMin = 0;        // position for the serco to return to
int degree   = angleMin; // variable used to store the position of the servo

/******************************** CREATE METHODS *********************************/

void init()              // set up all values and objects for use in the program
{
  Serial.begin (9600);
  
  sonic.begin(buttonP, ledP, buzzerP);
  altim.begin(buttonP, ledP, buzzerP);
  myservo.attach(9);
  
  pinMode(buttonP, INPUT);
  pinMode(ledP,   OUTPUT);
}

void calibration()       // used for the calibration of the rangefinder and altimeter
{
  atltim.calibrate(100);
}

void takePicture()       // turns the motor to the max then returns it to the min
{
  for(; val<=90; v++)
  {
    myservo.write();
    delay(15);
  }
  delay(50);
  for(; val>=0; v--)
  {
    myservo.write();
    delay(15);
  }
}

void alert(int times)   // flash the led and sound the buzzer for number of times
{
  for(; times>=0; times--)
  {
    digitalWrite(ledP, HIGH);
    tone(buzzerP, 880, 1000);
    delay(1000);
    digitalWrite(ledP, LOW);
    noTone(buzzerP);
  }
}

/****************************** DEFAULT RUN METHODS ******************************/

void setup()           // initialize varibles, wait for button press, calibrate sensors
{
  init();
  
  boolean buttonPress;
  while(!buttonPress)
  {
    buttonPress = digitalRead(buttonP);
  }
  
  alert(3);
  calibration();
  alert(3);
}

void loop()           // tell user when height reached then take pictures until the ground is hit
{
  int     altimHeight = altim.getHeightAvg(100);
  int     sonicHeight = sonic.getDistance();
  boolean buttonPress = digitalRead(buttonP);
  
  if(sonicHeight > 400 || sonicHeight == null){
    sonicHeight = altimHeight;
  }
  
  if(!hReached)
  {
    if(altimHeight < hTarget)
    {
      alert(1);
      delay(1000);
    }
    if(altimHeight > hTarget)
    {
      alert(2);
      delay(1000);
    }
    if(altimHeight == hTarget)
    {
      alert(5);
      hReached = true;
      delay(1000);
    }
  }
  
  if(hReached)
  {
    if(altimHeight > 1 || sonicHeight > 10)
    {
      takePicture();
    } else {
      alert(1);
      delay(3000);
    }
  }
  
}

