#include "Arduino.h"
#include "Motor.h"
#define pi 3.141592

//Constructor
Motor::Motor(int pinA, int pinB, float wheelRadius, int PPR) {
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  this->pinA = pinA;
  this->pinB = pinB;
  this->activePin = pinA;
  this->radius = wheelRadius;
  this->PPR = PPR;
};

/*
   forwards: Moves a motor forwards by a certain velocity
   velocity: Motor strength <0 to 255>
*/
void Motor::forwards(int velocity) {
  analogWrite(this->pinA, velocity);
  analogWrite(this->pinB, 0);
};

/*
   backwards: Moves a motor backwards by a certain velocity
   velocity: Motor strength <0 to 255>
*/
void Motor::backwards(int velocity) {
  analogWrite(this->pinA, 0);
  analogWrite(this->pinB, velocity);
};

/*
   turn: Turns a motor safely forwards or backwards
   velocity: Motor strength <-255 to 255>
*/
void Motor::turn(int velocity) {
  if (velocity > 0) {
    this->activePin = this->pinA;
  }
  else {
    this->activePin = this->pinB;
  }
  Serial.println("Active pin: " + String(this->activePin));
  int radiansOmega = velocity / this->radius;
  this->setSpeed = radiansOmega / (2 * pi);

};

void Motor::increaseCounter() {
  this->encoderPulses++;
}

void Motor::regulatePulse(float timeBetweenCalculations) {
  this->RPM = (this->encoderPulses * (60 / timeBetweenCalculations)) / this->PPR;
  Serial.println(encoderPulses);
  this->encoderPulses = 0;
  this->realSpeed = this->RPM;
  if (this->setSpeed != 0) {
    this->errorSpeed = this->setSpeed - this->realSpeed;
    this->PWM = this->errorSpeed * this->kp + this->sumErrorSpeed * this->ki + (this->errorSpeed - this->previousErrorSpeed) * this->kd;
    this->previousErrorSpeed = this->errorSpeed;  //save last (previous) error
    this->sumErrorSpeed += this->errorSpeed; //sum of error
    if (this->sumErrorSpeed > 4000) this->sumErrorSpeed = 4000;
    if (this->sumErrorSpeed < -4000) this->sumErrorSpeed = -4000;
  }
  else {
    this->errorSpeed = 0;
    this->previousErrorSpeed = 0;
    this->sumErrorSpeed = 0;
    this->PWM = 0;
  }

  //update new speed
  if (this->PWM < 255 & this->PWM > 0) {
    analogWrite(this->activePin, this->PWM); //set motor speed
  }
  else {
    if (this->PWM > 255) {
      analogWrite(this->activePin, 255);
    }
    else {
      analogWrite(this->activePin, 0);
    }
  }
}

void Motor::setVelocity(int velocity) {
  this->setSpeed = velocity;
}

int Motor::getRPM(){
  return this->RPM;
}
