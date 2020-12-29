#include <Arduino.h>

#define PWM1 PA0
#define PWM2 PA1
#define PWM3 PA2
#define PWM4 PA3

void setup()
{
  HardwareTimer *Timer1 = new HardwareTimer(TIM2);
  Timer1->setPWM(1, PWM1, 60, 0);
  Timer1->setPWM(2, PWM2, 60, 0);
  Timer1->setPWM(3, PWM3, 60, 0);
  Timer1->setPWM(4, PWM4, 60, 0);


  while(1){
    for (int i = 0; i != 65535; ++i){
      TIM2->CCR1 = i;
      delayMicroseconds(10);
    }
    for (int i = 0; i != 65535; ++i){
      TIM2->CCR2 = i;
      delayMicroseconds(10);
    }
    for (int i = 0; i != 65535; ++i){
      TIM2->CCR3 = i;
      delayMicroseconds(10);
    }
    for (int i = 0; i != 65535; ++i){
      TIM2->CCR4 = i;
      delayMicroseconds(10);
    }
  }
}

void loop() {

}
