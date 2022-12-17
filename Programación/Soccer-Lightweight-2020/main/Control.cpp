#include "Control.h"
#include "Motor.h"
#include"IRsensor.h"
#include"Arduino.h"
#include <math.h>
#include<stdlib.h>
#define pi 3.1415926535897936

Control::Control(Motor* A, Motor* B, Motor* C, ir_sensor* IR1, ir_sensor* IR2, ir_sensor* IR3, ir_sensor* IR4, int radius, bool checkWhites) {
  this->A = A;
  this->B = B;
  this->C = C;
  this->radius = radius;
  this->checkWhites = checkWhites;
  this->IR1 = IR1;
  this->IR2 = IR2;
  this->IR3 = IR3;
  this->IR4 = IR4;

}

Control::Control(Motor* A, Motor* B, Motor* C, int radius) {
  this->A = A;
  this->B = B;
  this->C = C;
  this->checkWhites = 0;
  this->radius = radius;

}

void Control::moveTo(float degree, float strength, float setOmega, float actOmega) {
  /*
    Function that runs motors at a calculated RPM.
    Input:
      degree: is the degree of the direction of the ball.
      strength: is the signal strength measured by the seeker.
      setOmega: is the absolute angle towards the which the robot has to rotate.
      actOmega: is the absolute angle the robot is actually facing.
    Output:
      None
  */
  //actOmega = degree;
  bool readWhite = 0;
  float vector = 0;
  if (strength <= 100 && strength > 0) {
    vector = 300 + (strength * 200 / 100);
  }
  else {
    if (strength >= 100) {
      vector = 300;
    }
    else {
      vector = 500;
    }
  }
  if (degree == 0) {
    vector = 500;
  }
  //Serial.println("Delta Omega: " + String(setOmega-actOmega));
  this->rotationError = setOmega - actOmega;
  this->omega = (this->rotationError * pi / 180 * this->kpr) + (this->sumRotationError * pi / 180 * this->kir) + ((this->rotationError - this->pastRotationError) * pi / 180 * this->kdr);
  Serial.println(omega);
  float A_velocity = vector * cos((30 - degree) * pi / 180) - (this->omega * this->radius);
  float B_velocity = vector * cos((150 - degree) * pi / 180) - (this->omega * this->radius);
  float C_velocity = vector * cos((270 - degree) * pi / 180) - (this->omega * this->radius);
  this->pastRotationError = this->rotationError;
  this->sumRotationError += this->rotationError;
  if (this->sumRotationError > 4000) {
    this->sumRotationError = 4000;
  }
  if (this->sumRotationError < -4000){
    this->sumRotationError = -4000;
  }
  if (this->checkWhites) {
    readWhite = this->IR1->readWhite() || this->IR2->readWhite() || this->IR3->readWhite() || this->IR4->readWhite();
  }
  //Serial.println("A_velocity: " + String(A_velocity) + " B_velocity: " + String(B_velocity) + " C_velocity: " + String(C_velocity));;
  if (this->checkWhites) {
    if (readWhite) {
      Serial.println("STOP");
      this->A->turn(0);
      this->B->turn(0);
      this->C->turn(0);
      /*if (abs(this->lastDegree - degree) > 60) {
        this->A->turn(A_velocity);
        this->B->turn(B_velocity);
        this->C->turn(C_velocity);
        }
        else {
        this->A->turn(0);
        this->B->turn(0);
        this->C->turn(0);
        this->lastDegree = degree;

        }*/
    }
    else {
      Serial.println("MOVING");
      this->A->turn(A_velocity);
      this->B->turn(B_velocity);
      this->C->turn(C_velocity);
    }
  }
  else {
    this->A->turn(A_velocity);
    this->B->turn(B_velocity);
    this->C->turn(C_velocity);
  }

}

void Control::moveTo(float x, float y, int velocity) {
  float angle = atan2(y, x);
  A->turn(velocity * cos(-angle + pi * 0.166F));
  B->turn(velocity * cos(-angle + pi * 0.166F * 5));
  C->turn(velocity * cos(-angle + pi * 0.166F * 9));

}
