/*
    Class for an analog IR sensor.  16/02/2020.
*/

#include <Arduino.h>
#include "IRsensor.h"

ir_sensor::ir_sensor(int pin){
    this->pin = pin;
    pinMode(this->pin,INPUT);
}

int ir_sensor::read(){
    return analogRead(this->pin);
}
