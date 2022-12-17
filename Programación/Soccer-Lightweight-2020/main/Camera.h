#ifndef Camera_h
#define Camera_h

#define I2C
#ifdef I2C
#include<Pixy2I2C.h>
#endif
#include"Arduino.h"

class Camera {
  public:
    Pixy2I2C cam;
    Camera();
    void init();
    void calculateGoal();
    int getGoalX();
    int getGoalY();
    int getGoalWidth();
    int getGoalHeight();
    int getGoalAge();
    float getAlphaDegree();
  private:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int age = 0;
    float alphaDegree = 0;
};

#endif
