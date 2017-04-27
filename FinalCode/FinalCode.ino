#define trigPin 10
#define echoPin 13
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);

  val = analogRead(potpin);            
  val = map(val, 0, 1023, 0, 180);   
  myservo.write(val);     
  delay(15);
}

void loop() {
    
  float distance = getDistance();
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else if(distance >= 12 || distance <= 10) {
    val = 20;            
    val = map(val, 0, 1023, 0, 180);   
    myservo.write(val);
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    val = analogRead(potpin);            
    val = map(val, 0, 1023, 0, 180);   
    myservo.write(val);  
    delay(500);
  }
  delay(500);
}

float getDistance(){
  float duration;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
       
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
        
  duration = pulseIn(echoPin, HIGH);
  return (duration / 2) * 0.0344;
}

