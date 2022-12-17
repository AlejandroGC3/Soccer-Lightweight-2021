#include "Arduino.h"
#include"seeker.h"
#include"Motor.h"
int mot = 0;
Motor A(29, 30, 2.25, 245);
Motor B(7, 8, 2.25, 245);
Motor C(5, 6, 2.25, 245);
int encA = 28;
int encB = 27;
int encC = 26;
int vel = 0;
IntervalTimer pid;

Seeker seekr;
void adelante(int rpm) {
  A.turn(rpm);
  B.turn(-rpm);
  C.turn(0);
}

void atras(int rpm) {
  A.turn(-rpm);
  B.turn(rpm);
  C.turn(0);
}

void freno() {
  A.turn(0);
  B.turn(0);
  C.turn(0);
}

void derecha(int rpm) {
  A.turn(rpm);
  B.turn(rpm);
  C.turn(-rpm);
}

void izquierda(int rpm) {
  A.turn(-rpm);
  B.turn(-rpm);
  C.turn(rpm);
}

void giroi(int rpm) {
  A.turn(-rpm);
  B.turn(-rpm);
  C.turn(-rpm);
}


void girod(int rpm) {
  A.turn(rpm);
  B.turn(rpm);
  C.turn(rpm);
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  seekr.read();
  int section = seekr.getBallSector();
  Serial.println(section);
  if (section == 0) {
    atras(300);
    }
    else if (section == 1) {
    atras(300);
    }
    else if (section == 2) {
      atras(300);
    }
    else if (section == 3) {
      izquierda(300);
    }
    else if (section == 4) {
      izquierda(300);
    }
    if (section == 5) {
        ///////////////////////////////FIN DE IR HACIA LA PORTERIA AL TENER LA PELOTA////////////////////////////////////////////
      adelante(300);
    }
    else if (section == 6) {
      derecha(300);
    }
    else if (section == 7) {
      derecha(300);
    }
    else if (section == 8) {
      atras(300);

    }
    else if (section == 9) {
    atras(300);
    }

}
