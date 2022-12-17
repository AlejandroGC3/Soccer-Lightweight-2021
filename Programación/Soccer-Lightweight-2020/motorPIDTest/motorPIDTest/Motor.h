#ifndef Motor_h
#define Motor_h

class Motor{
  public:
    Motor(int pinA, int pinB, float wheelRadius, int PPR);
    void turn(int velocity);
    void setVelocity(int velocity);
    int getRPM();
    void increaseCounter();
    void regulatePulse(float timeBetweenCalculations);

  private:
    int pinA, pinB;
    int activePin = 0;
    volatile int encoderPulses = 0;
    int PPR = 0, RPM = 0;
    void forwards(int velocity);
    void backwards(int velocity);
    int radius = 0;
    //variables used for PID
    // 0.65 0.08 0.04
    float kp = 0.65,ki = 0.08,kd = 0.04;
    int setSpeed = 200, realSpeed = 0, errorSpeed = 0;
    int sumErrorSpeed = 0, previousErrorSpeed = 0;
    int PWM = 0;
};



#endif
