
#ifndef Control_h
#define Control_h

#include"Motor.h"
#include"IRsensor.h"

class Control{
    public:
        Control(Motor* A, Motor* B, Motor*C,ir_sensor* IR1, ir_sensor* IR2, ir_sensor* IR3, ir_sensor* IR4, ir_sensor* IR5);
        void MoveTo(float,float,float,float);
        void MoveTo(float,float,int);
    private:
        Motor *A;
        Motor *B;
        Motor *C;
        ir_sensor *IR1, *IR2, *IR3, *IR4, *IR5;
        int irLimit1 = 0,irLimit2 = 0,irLimit3 = 0,irLimit4 = 0,irLimit5 = 0;
        int lastDegree = 0;
        int radius;
};

#endif
