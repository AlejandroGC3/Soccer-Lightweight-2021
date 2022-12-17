#include "Control.h"
#include "Motor.h"
#include"IRsensor.h"
#include <math.h>
#include<stdlib.h>
#define pi 3.1415926535897936

Control::Control(Motor* A, Motor* B, Motor* C,ir_sensor* IR1, ir_sensor* IR2, ir_sensor* IR3, ir_sensor* IR4, ir_sensor* IR5){
    this->A = A;
    this->B = B;
    this->C = C;
    this->IR1 = IR1;
    this->IR2 = IR2;
    this->IR3 = IR3;
    this->IR4 = IR4;
    
}

void Control::MoveTo(float degree,float strength,float setOmega,float actOmega){
    /*
    Function that runs motors at a calculated linear speed.
    Input:
        degree: is the degree of the direction of the ball.
        strength: is the signal strength measured by the seeker.
        setOmega: is the absolute angle towards the which the robot has to rotate.
        actOmega: is the absolute angle the robot is actually facing.
    Output:
        None
    */
    float vector = 0;
    if(140 - strength > 0 && 140 - strength < 140){
        vector = 1632 + strength*6529/140;
    }
    else{
        if(140-strength <= 0){
            vector = 1632;
        }
        else{
            vector = 6529;
        }
    }
    float A_velocity = vector*cos(30-degree)/*+((setOmega-actOmega)*pi*this->radius)*/;
    float B_velocity = vector*cos(150-degree)/*+((setOmega-actOmega)*pi*this->radius)*/;
    float C_velocity = vector*cos(270-degree)/*+((setOmega-actOmega)*pi*this->radius)*/;
    bool readWhite = this->IR1->read() < this->irLimit1 && this->IR2->read() < this->irLimit2 
    && this->IR3->read() < irLimit3 && this->IR4->read() < this->irLimit4 && this->IR5->read() < irLimit5;

    if(readWhite){
        if(abs(this->lastDegree - degree) > 60){
            this->A->turn(A_velocity);
            this->B->turn(B_velocity);
            this->C->turn(C_velocity);
        }
        else{
            this->A->turn(0);
            this->B->turn(0);
            this->C->turn(0);
            this->lastDegree = degree;
        
        }
    }
    else{
        this->A->turn(A_velocity);
        this->B->turn(B_velocity);
        this->C->turn(C_velocity);
    }   

}

void Control::MoveTo(float x, float y, int velocity) {
  float angle = atan2(y, x);
  A->turn(velocity * cos(-angle + pi * 0.166F));
  B->turn(velocity * cos(-angle + pi * 0.166F * 5));
  C->turn(velocity * cos(-angle + pi * 0.166F * 9));
 
}
