//PID dc motor speed control for ATTiny85. Lions R.C.
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

IntervalTimer myTimer;
//Declaring PID constants
float kp = 0.07;
float kd = 0.03;
float ki = 0.05;

//Motor previous speed
int pv_speed = 0;
//Error speed
int e_speed = 0;
//Previous error speed
int e_speed_pre = 0;
//Sum of error speed
int e_speed_sum=0;

//Selected speed(rpm)
int set_speed = 100;

//Motor start variable
bool m_s = 1;

//PWM pulse strength
int pwm_pulse = 0;

//Motor ppr
const int ppr = 980 / 4;
//Motor input pin numbers.
uint8_t mot1 = 4;
uint8_t mot2 = 5;

//Encoder channel A
uint8_t encA = 2;

//Encoder pulse counter
volatile int cnt = 0;

bool mv = 0;

void setup() {

  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(3,INPUT);

  attachInterrupt(digitalPinToInterrupt(3),contar,RISING);



  myTimer.begin(calcular,20000);
 


}

void contar() {
  cnt++;

}


//Activates at 0.125s
void calcular(){ 
  pv_speed = 60*(cnt/ppr)/0.1;  //calculate motor speed, unit is rpm
  cnt=0;
  //print out speed
  if(abs(set_speed-pv_speed) <= 10)PORTB |=(1 << 3);
  else PORTB &= ~(1<<3);
  
  if (m_s){
     e_speed = set_speed - pv_speed;
     pwm_pulse = e_speed*kp + e_speed_sum*ki + (e_speed - e_speed_pre)*kd;
     e_speed_pre = e_speed;  //save last (previous) error
     e_speed_sum += e_speed; //sum of error
     if (e_speed_sum >4000) e_speed_sum = 4000;
     if (e_speed_sum <-4000) e_speed_sum = -4000;
   }
   else{
     e_speed = 0;
     e_speed_pre = 0;
     e_speed_sum = 0;
     pwm_pulse = 0;
   }
  //update new speed
   if(pwm_pulse <255 & pwm_pulse >0){
     analogWrite(mot1,pwm_pulse);  //set motor speed 
   }else{
     if(pwm_pulse>255){
       analogWrite(mot1,255);
     }else{
       analogWrite(mot1,0);
     }
   }
}

 

void loop() {
  // put your main code here, to run repeatedly:



}
