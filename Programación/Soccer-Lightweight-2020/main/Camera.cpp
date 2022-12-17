#include"Arduino.h"
#include"Camera.h"
#include<math.h>
#include<Pixy2.h>
#include<Pixy2I2C.h>
#define pi 3.141592
Camera::Camera(){}

void Camera::init(){
  this->cam.init();
}

void Camera::calculateGoal() {
  int maxWidth = 0;
  int chosenIndex = 0;
  cam.ccc.getBlocks();

  if (cam.ccc.numBlocks) {
    for (int i = 0; i < cam.ccc.numBlocks; i++) {
      if (cam.ccc.blocks[i].m_signature == 1) {
        int width = cam.ccc.blocks[i].m_width;
        if (width >= maxWidth) {
          if (width == maxWidth) {
            if (abs(315 / 2 - cam.ccc.blocks[i].m_x) < abs(315 / 2 - cam.ccc.blocks[chosenIndex].m_x)) {
              maxWidth = width;
              chosenIndex = i;
            }
          }
          else {
            maxWidth = width;
            chosenIndex = i;
          }
        }
      }
    }

    this->width = cam.ccc.blocks[chosenIndex].m_width;
    this->height = cam.ccc.blocks[chosenIndex].m_height;
    this->x = cam.ccc.blocks[chosenIndex].m_x;
    this->y = cam.ccc.blocks[chosenIndex].m_y;
    this->age = cam.ccc.blocks[chosenIndex].m_age;
    float deltax = 315/2-(float)this->x;
    float deltay = 207/2;
    float rad = atan(deltax/deltay);
    float deg = rad*180/pi;
    //Serial.println("Deltax: " +String(deltax)+ " Deltay: " + String(deltay) + " rad: " + String(rad) + " deg: " + String(deg)) ;
    this->alphaDegree = deg*-1.0;
  }
  else{
    this->width = 0;
    this->height = 0;
    this->x = 0;
    this->y = 0;
    this->age = 0;
    this->alphaDegree = 0;
  }
}

int Camera::getGoalX(){
  return this->x;
}

int Camera::getGoalY(){
  return this->y;
}

int Camera::getGoalWidth(){
  return this->width;
}

int Camera::getGoalHeight(){
  return this->height;
}

int Camera::getGoalAge(){
  return this->age;
}

float Camera::getAlphaDegree(){
  return this->alphaDegree;
}
