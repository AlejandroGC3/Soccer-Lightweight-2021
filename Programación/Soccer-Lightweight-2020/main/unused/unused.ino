#include "Arduino.h"
#include"seeker.h"
#include"Motor.h"
int mot = 0;
Motor A(9, 10, 2.25, 245);
Motor B(11, 12, 2.25, 245);
Motor C(5, 6, 2.25, 245);
const uint16_t t1_comp = 7813;
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(19), countA, RISING);
  attachInterrupt(digitalPinToInterrupt(2), countB, RISING);
  //attachInterrupt(digitalPinToInterrupt(18),countC,RISING);
  //Activate timerA compare output
  TIMSK1 |= (1 << 1);

  //Clear TCCR1A Registers, timer1 control register A, which arduino presets for analogWrite
  TCCR1A = 0;

  //Set CTC mode so that the timer counter resets when it gets to the comparing point it resets to 0
  TCCR1A &= ~(1 << WGM11);
  TCCR1A &= ~(1 << WGM10);
  TCCR1B |= (1 << WGM12);
  TCCR1B &= ~(1 << WGM13);

  //Setting the prescaler to 1024
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B |= (1 << CS10);

  //Reset timer and set compare value
  TCNT1 = 0;
  OCR1A = t1_comp;
}

ISR(TIMER1_COMPA_vect) {
  if (mot == 0) {
    A.regulatePulse(0.5);
    mot++;
  }
  else if (mot == 1) {
    B.regulatePulse(0.5);
    mot++;
  }
  else if (mot == 2) {
    C.regulatePulse(0.5);
    mot = 0;
  }
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
    A.setVelocity(Serial.parseInt());
  }
  //Serial.println(String(A.getRPM()) + "\t" + String(B.getRPM()) + "\t" + String(C.getRPM()) + "\t 200");

}
