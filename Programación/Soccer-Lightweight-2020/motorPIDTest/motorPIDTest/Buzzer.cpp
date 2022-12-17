#include "Arduino.h"
#include "Buzzer.h"

Buzzer::Buzzer(int pin){
  _pin = pin;
  pinMode(_pin, OUTPUT);
  
}

void Buzzer::beep(){
  digitalWrite(_pin, HIGH);
  delay(50);
  digitalWrite(_pin, LOW);
  delay(50);
}
