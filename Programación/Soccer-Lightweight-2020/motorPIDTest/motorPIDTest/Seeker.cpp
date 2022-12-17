/*
    Class for control of the Lego v2 Infrared Seeker. 16/02/2020.
*/

#include <Arduino.h>
#include<math.h>
#include "Seeker.h"

Seeker::Seeker(){
    InfraredSeeker::Initialize();
}

void Seeker::ReadSeeker(){
    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    this->ballSector = InfraredBall.Direction;
    this->ballStrength = InfraredBall.Strength;
}

int Seeker::GetBallDegree(){
    return this->ballSector * 30 -150;
}

int Seeker::GetBallStrength(){
    return this->ballStrength;
}

void Seeker::updateBallPosition(){
    int theta = this->ballSector * 30 - 150;
    this->ballX =  this->ballStrength * cos(theta);
    this->ballY = this->ballStrength * sin(theta);
}

int Seeker::getBallXCoord(){
    return this->ballX;
}

int Seeker::getBallYCoord(){
    return this->ballY;
}
