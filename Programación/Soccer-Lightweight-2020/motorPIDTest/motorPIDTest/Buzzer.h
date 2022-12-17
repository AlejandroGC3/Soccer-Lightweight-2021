#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer{
  public:
    Buzzer(int);
    void beep();
    
  private:
    byte _pin = 28;
};

#endif
