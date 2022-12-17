/*
    distance.h : Library for using a distance sensor, ultrasonic or laser. 16/02/2020.
*/

#ifndef Distance_h
#define Distance_h

class Distance_sensor{
    public:
        Distance_sensor(int, int);
        Distance_sensor(int);
        int read_distance();
    
    private:
        bool type = 0;
        int pin1 = 0,pin2 = 0;

};



#endif
