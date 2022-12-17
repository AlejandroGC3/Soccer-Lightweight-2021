#include "Arduino.h"
#include "Motor.h"
#define pi 3.141592

//Constructor
Motor::Motor(int pinA, int pinB, float wheelRadius, int PPR) {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  this->pinA = pinA;
  this->pinB = pinB;
  this->activePin = pinA;
  this->lowPin = pinB;
  this->radius = wheelRadius;
  this->PPR = PPR;
};

/*
   turn: Turns a motor safely forwards or backwards
   velocity: Motor strength <-255 to 255>
*/
void Motor::turn(int velocity) {
  if (velocity != 0) {
    if (velocity > 0) {
      this->activePin = this->pinA;
      this->lowPin = this->pinB;
      if (cycle == 0) {
        this->prevDir = this->dir;
      }
      this->dir = 0;
    }
    else {
      this->activePin = this->pinB;
      this->lowPin = this->pinA;
      if (cycle == 0) {
        this->prevDir = this->dir;
      }
      this->dir = 1;
      velocity = abs(velocity);
    }
    //Serial.println("Active pin: " + String(this->activePin));
    this->setSpeed = velocity;
  }
  else {
    this -> setSpeed = 0;
  }
  this->cycle = 1;
};

void Motor::increaseCounter() {
  this->encoderPulses++;
}

void Motor::regulatePulse(float timeBetweenCalculations) {
  this->RPM = (this->encoderPulses * (60 / timeBetweenCalculations)) / this->PPR;
  this->encoderPulses = 0;
  this->realSpeed = this->RPM;
  this->cycle = 0;
  if (this->setSpeed != 0) {
    if (this->prevDir != this->dir) {
      analogWrite(this->activePin, 0);
      analogWrite(this->lowPin, 0);
    }
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
  if (this->PWM <= 255 && this->PWM > 0) {
    analogWrite(this->activePin, this->PWM); //set motor speed
    digitalWrite(this->lowPin, LOW);
  }
  else {
    if (this->PWM > 255) {
      analogWrite(this->activePin, 255);
      digitalWrite(this->lowPin, LOW);
    }
    else {
      analogWrite(this->activePin, 0);
      analogWrite(this->lowPin, 0);
    }
  }
}

void Motor::setVelocity(int velocity) {
  this->setSpeed = velocity;
}

int Motor::getRPM() {
  return this->RPM;
}
