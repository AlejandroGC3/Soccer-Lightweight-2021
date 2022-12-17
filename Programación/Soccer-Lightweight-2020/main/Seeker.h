/*
    Class for control of the Lego v2 Infrared Seeker. 16/02/2020.
*/

#ifndef Seeker_h
#define Seeker_h

#include <HTInfraredSeeker.h>

class Seeker {
  public:
    Seeker();
    void read();
    void updateBallPosition();
    float getBallDegree();
    float getBallStrength();
    float getBallXCoord();
    float getBallYCoord();
    int getBallSector();
  private:
    int lastBallSector = 0;
    int ballSector = 0;
    int ballStrength = 0;
    int ballX = 0;
    int ballY = 0;

};

#endif
