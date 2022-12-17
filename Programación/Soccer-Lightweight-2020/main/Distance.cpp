/*
    distance.h : Library for using a distance sensor, ultrasonic or laser. 16/02/2020.
*/

#include "Arduino.h"
#include "Distance.h"

Distance_sensor::Distance_sensor(int pin1, int pin2){
    this->pin1 = pin1; 
    this->pin2 = pin2;
    this->type = 1;
    pinMode(this->pin1,OUTPUT);
    pinMode(this->pin2,INPUT);
}

Distance_sensor::Distance_sensor(int pin1){
    this->pin1 = pin1;
    this->type = 0;
    pinMode(this->pin1,INPUT);
}

int Distance_sensor::read_distance(){
    if(!this->type){
        return(pulseIn(this->pin1,HIGH)/10);
    }
    else{
        digitalWrite(this->pin1,LOW);
        delayMicroseconds(2);
        digitalWrite(this->pin1,HIGH);
        delayMicroseconds(10);
        digitalWrite(this->pin1,LOW);
        delayMicroseconds(2);
        return pulseIn(this->pin2,HIGH)/58;
    }
}
