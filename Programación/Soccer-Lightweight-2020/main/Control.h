
#ifndef Control_h
#define Control_h

#include"Motor.h"
#include"IRsensor.h"

class Control{
    public:
        Control(Motor* A, Motor* B, Motor*C,ir_sensor* IR1, ir_sensor* IR2, ir_sensor* IR3, ir_sensor* IR4,int radius,bool checkWhites);
        Control(Motor* A, Motor* B, Motor*C,int radius);
        void moveTo(float,float,float,float);
        void moveTo(float,float,int);
    private:
        Motor *A;
        Motor *B;
        Motor *C;
        ir_sensor *IR1, *IR2, *IR3, *IR4, *IR5;
        int checkWhites = 0;
        int irLimit1 = 800,irLimit2 = 800,irLimit3 = 800,irLimit4 = 750;
        int lastDegree = 0;
        int radius = 0;
        float rotationError = 0, pastRotationError = 0, sumRotationError = 0;
        float kpr = 6,kir = 0.3,kdr = 0.3;
        float omega = 0;
};

#endif
