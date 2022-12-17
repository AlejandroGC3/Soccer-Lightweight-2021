#include"Arduino.h"
#include"seeker.h"
#include"Motor.h"
#include"Control.h"
#include"IRsensor.h"
#include"compass.h"
#include"Camera.h"

#define robotRadius 8
#define wheelRadius 2.25

Camera cam;

compass_sensor compass;

Seeker seekr;

ir_sensor ir1(20, 980);
ir_sensor ir2(17, 980);
ir_sensor ir3(16, 980);
ir_sensor ir4(15, 850);

Motor A(29, 30, wheelRadius, 245);
Motor B(7, 8, wheelRadius, 245);
Motor C(5, 6, wheelRadius, 245);

Control cntrl(&A, &B, &C, &ir1, &ir2, &ir3, &ir4, robotRadius, 0);

int encA = 28;
int encB = 27;
int encC = 26;

int pastTime = 0;

IntervalTimer pid;

void run_pid() {
  A.regulatePulse(0.01);
  B.regulatePulse(0.01);
  C.regulatePulse(0.01);
}

void countA() {
  A.increaseCounter();
}

void countB() {
  B.increaseCounter();
}

void countC() {
  C.increaseCounter();
}

void setup() {
  Serial.begin(115200);
  pid.begin(run_pid, 10000);
  attachInterrupt(digitalPinToInterrupt(encA), countA, RISING);
  attachInterrupt(digitalPinToInterrupt(encB), countB, RISING);
  attachInterrupt(digitalPinToInterrupt(encC), countC, RISING);
  pastTime = millis();
  compass.init();
  cam.init();

}

void loop() {
  if (millis() - pastTime > 3) {
    compass.calculateRelativeDegree();
    seekr.read();
  }
  cam.calculateGoal();
  int alpha = cam.getAlphaDegree();
  int delta = compass.getDeltaDegree();
  float degree = seekr.getBallDegree();
  float strength = seekr.getBallStrength();
  //Serial.println("Initial Degree: " + String(compass.getInitDegree()) + " Delta degree: " + String(delta) + " Degree: " + String(degree) + " Strength: " + String(strength) + " Alpha: " + String(alpha));
  //Serial.println("Degree: " + String(degree) + " Strength: " + String(strength));
  //Serial.println("ir1: " + String(ir1.readWhite()) + " ir2: " + String(ir2.readWhite()) + " ir3: " + String(ir3.readWhite()) + " ir4: " + String(ir4.readWhite()));
  Serial.println(" 0 " + String(delta));
  cntrl.moveTo(delta,50,0,delta);
  /*if (delta < -45 || delta > 45) {
    cntrl.moveTo(degree, strength, 0, delta);
  }
  else {
    if (degree != 0) {
      cntrl.moveTo(degree, strength, 0, degree);
    }
    else if (degree == 0 && alpha != 0) {
      cntrl.moveTo(alpha, strength, 0, alpha);
    }
    else if (degree == 0 && alpha == 0) {
      cntrl.moveTo(delta, 50, 0, delta);
    }
  }*/

}
