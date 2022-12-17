#include "Arduino.h"
#include"seeker.h"
#include"Motor.h"
int mot = 0;
Motor A(5, 6, 2.25, 245);
Motor B(7, 8, 2.25, 245);
Motor C(29, 30, 2.25, 245);
const uint16_t t1_comp = 1563;
IntervalTimer pid;
void setup() {
  Serial.begin(9600);
  pid.begin(run_pid,100000);
  attachInterrupt(digitalPinToInterrupt(26), countA, RISING);
  attachInterrupt(digitalPinToInterrupt(27), countB, RISING);
  attachInterrupt(digitalPinToInterrupt(28),countC,RISING);

}

void run_pid() {
    A.regulatePulse(0.1);
    B.regulatePulse(0.1);
    C.regulatePulse(0.1);
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

void loop() {
  if (Serial.available()) {
    int vel = Serial.parseInt();
    A.setVelocity(vel);
    B.setVelocity(vel);
    C.setVelocity(vel);
  }
  Serial.println(String(A.getRPM()) + " " + String(B.getRPM()) + " " + String(C.getRPM()) + " 200");

}
