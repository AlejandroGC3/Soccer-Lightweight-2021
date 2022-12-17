/*
    Library to use LSM303 compass. 16/02/2020.
*/

#ifndef compass_sensor_h
#define compass_sensor_h

#include <LSM303.h>
#include <Wire.h>
#include"Arduino.h"

class compass_sensor{
    public:
        compass_sensor();
        void init();
        void calculateRelativeDegree();
        int getRelativeDegree();
        int getDeltaDegree();
        int getInitDegree();
        
    private:
        LSM303 compass;
        int initdeg = 0;
        int state = 0;
        float relativeDegree = 0;
};

#endif
