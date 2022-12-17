/*
    Class for control of the Lego v2 Infrared Seeker. 16/02/2020.
*/

#ifndef Seeker_h
#define Seeker_h

#include <HTInfraredSeeker.h>

class Seeker{
    public:
        Seeker();
        void ReadSeeker();
        void updateBallPosition();
        int GetBallDegree();
        int GetBallStrength();
        int getBallXCoord();
        int getBallYCoord();
        int ballSector;
        int ballStrength;
        int ballX;
        int ballY;

};

#endif
