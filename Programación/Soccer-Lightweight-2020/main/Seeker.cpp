/*
    Class for control of the Lego v2 Infrared Seeker. 16/02/2020.
*/

#include <Arduino.h>
#include<math.h>
#include "Seeker.h"

Seeker::Seeker() {
  InfraredSeeker::Initialize();
}

void Seeker::read() {
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  if (this->ballSector != 0) {
    this->lastBallSector = this->ballSector;
  }
  this->ballSector = InfraredBall.Direction;
  this->ballStrength = InfraredBall.Strength;

  this->ballX =  this->ballStrength * cos(this->ballSector * 30 - 150);
  this->ballY = this->ballStrength * sin(this->ballSector * 30 - 150);
}

float Seeker::getBallDegree() {
  if (this->ballSector != 0) {
    if (this->ballSector >= 2 && this->ballSector <= 8) {
      return this->ballSector * 30 - 150;
    }
    else if (this->ballSector > 8
    ) {
      return 180;
    }
    else {
      return 180;
    }
  }
  else {
    return 180;
  }
}


float Seeker::getBallStrength() {
  return this->ballStrength;
}

float Seeker::getBallXCoord() {
  return this->ballX;
}

float Seeker::getBallYCoord() {
  return this->ballY;
}

int Seeker::getBallSector() {
  return this->ballSector;
}
