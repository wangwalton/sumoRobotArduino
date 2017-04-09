#include "Timer.h"

void motorForward(int motorSpeed);
void motorBackward(int motorSpeed);
void motorLeft(int motorSpeed);
void motorRight(int motorSpeed);
void motorBackRight(int motorSpeed);
void motorBackLeft(int motorSpeed);
void motorStop();
void attackMasterPlan();

//enter desired speed (0~255)
int motorFastest = 255;
int motorFaster = 230;
int motorSlow = 180;
int motorDefault = 200;

//enter appropriate pin number
int pin1 = 11; //right motor speed
int pin2 = 6; //left motor speed
int pin3 = 12; //right motor
int pin4 = 13; //right motor
int pin5 = 8; //left motor
int pin6 = 7; //left motor

//sensors
int lineSensor1;
int lineSensor2;
int infraredSensor;

//enter reading period (ms)
int readingPeriod = 100;

Timer t;



void motorForward(int motorSpeed){
  analogWrite(pin1, motorSpeed);
  analogWrite(pin2, motorSpeed);

  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, LOW);
}

void motorBackward(int motorSpeed){
  analogWrite(pin1, motorSpeed);
  analogWrite(pin2, motorSpeed);

  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, HIGH);
}

void motorLeft(int motorSpeed){
  analogWrite(pin1, motorSpeed);
  analogWrite(pin2, motorSpeed/1.5);

  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, LOW);
}

void motorRight(int motorSpeed){
  analogWrite(pin1, motorSpeed/1.5);
  analogWrite(pin2, motorSpeed);

  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, LOW);
}


//didnt change the direction of this :( cuz too much work
void motorBackLeft(int motorSpeed){
  analogWrite(pin1, motorSpeed);
  analogWrite(pin2, motorSpeed/1.5);

  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
}


void motorBackRight(int motorSpeed){
  analogWrite(pin1, motorSpeed/1.5);
  analogWrite(pin2, motorSpeed);

  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, HIGH);
}

void motorStop(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
}

void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(pin5,OUTPUT);
  pinMode(pin6,OUTPUT);
  pinMode(A0,INPUT); //linePin1 23
  pinMode(A1,INPUT); //linePin2 24
  pinMode(A2,INPUT); //infraredPin 25

  //how long to delay
  delay(3000);

}

void loop() {
  lineSensor1 = analogRead(A0);
  lineSensor2 = analogRead(A1);
  infraredSensor = analogRead(A2);
  
  while (lineSensor1 == 0 && lineSensor2 == 0 && infraredSensor == 0) {
    motorLeft(motorFaster);
    delay(100);
    lineSensor1 = analogRead(A0);
    lineSensor2 = analogRead(A1);
    infraredSensor = analogRead(A2);
  }

  //if both sensors are on, turn left
  if (lineSensor1 != 0 && lineSensor2 != 0) {
    motorLeft(motorFaster);
    delay(500);
    motorForward(motorFaster);
    delay(200);
    motorLeft(motorFaster);
    delay(500);
    motorForward(motorFaster);
    delay(200);
    motorLeft(motorFaster);
    delay(500);
    motorForward(motorFaster);
    delay(200);
    motorLeft(motorFaster);
    delay(500);
    motorForward(motorFaster);
    delay(200);
  }

  ///if front on, move backward
  else if (lineSensor1 != 0) {
    motorBackward(motorFaster);
    delay(1000);
    motorBackRight(motorFaster);
    delay(2000);
  }

  //if infrared on
  else if(infraredSensor != 0) {
    if (infraredSensor < 155){
      motorForward(motorDefault);
    }
    else if(infraredSensor >= 155 && infraredSensor <= 300){
      motorForward(motorFaster);
    }
    else{
      motorForward(motorFastest);
    }
  }

  else {
    motorForward(motorDefault);
  }
}

