/*
    Class for an analog IR sensor.  16/02/2020.
*/

#include <Arduino.h>
#include "IRsensor.h"

ir_sensor::ir_sensor(int pin,int limit){
    this->pin = pin;
    this->limit = limit;
    pinMode(this->pin,INPUT);
}

int ir_sensor::read(){
    return analogRead(this->pin);
}

bool ir_sensor::readWhite(){
  return analogRead(this->pin) > this->limit;
}
