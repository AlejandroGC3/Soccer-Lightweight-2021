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
    bool dir = 0,prevDir = 0;
    int pinA = 0, pinB = 0;
    int activePin = 0,lowPin = 0;
    volatile int encoderPulses = 0;
    int PPR = 0, RPM = 0;
    void forwards(int velocity);
    void backwards(int velocity);
    int radius = 0;
    bool cycle = 0;
    //variables used for PID
    //Etiquetado p0.65 i0.08 d0.04
    //float kp = 0.55,ki = 0.07,kd = 0.02;
    //Sin etiquetas p0.55 i0.07 d0.02
    float kp = 0.95,ki = 0.12,kd = 0.05;
    int setSpeed = 0, realSpeed = 0, errorSpeed = 0, negSpeed = 0;
    int sumErrorSpeed = 0, previousErrorSpeed = 0;
    int PWM = 0;
};



#endif
