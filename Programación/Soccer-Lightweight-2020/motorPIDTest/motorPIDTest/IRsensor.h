/*
    Class for an analog IR sensor. 16/02/2020.
*/

#ifndef IRsensor_h
#define IRsensor_h

class ir_sensor{
    public:
        ir_sensor(int pin);
        int read();

    private:
        int pin = 0;

};

#endif
