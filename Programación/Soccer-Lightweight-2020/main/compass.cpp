/*
    Library to use LSM303 compass. 16/02/2020.
*/

#include "compass.h"
#include<LSM303.h>
#include"Arduino.h"
#include<Wire.h>

compass_sensor::compass_sensor() {

}

void compass_sensor::init() {
  Wire.begin();
  this->compass.init();
  this->compass.enableDefault();
  this->compass.m_min = (LSM303::vector<int16_t>) {
     +385,   -905,  +1600
  };
  this->compass.m_max = (LSM303::vector<int16_t>) {
    +5850,  +4524,  +7624
  };
  delay(500);
  this->compass.read();
  int head = this->compass.heading();
  this->initdeg = head;
  
}

void compass_sensor::calculateRelativeDegree() {
  this->compass.read();
  int head = ((int)this->compass.heading() - (int)this->initdeg + 360) % 360;
  this->relativeDegree = head;
}

int compass_sensor::getRelativeDegree() {
  return this->relativeDegree;
}

int compass_sensor::getDeltaDegree() {
  if (this->relativeDegree >= 180) {
    return (360 - this->relativeDegree);
  }
  else {
    return relativeDegree * -1;
  }
}

int compass_sensor::getInitDegree() {
  return this->initdeg;
}
