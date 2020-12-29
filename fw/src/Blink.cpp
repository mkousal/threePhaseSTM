/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

#ifndef LED_BUILTIN
  #define LED_BUILTIN PC13
#endif

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(PA3), PinMap_PWM);
  uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(PA3), PinMap_PWM));

  HardwareTimer *MyTim = new HardwareTimer(Instance);

  MyTim->setPWM(channel, PA3, 60, 10);

  while(1){

  }
}

void loop()
{
  // // turn the LED on (HIGH is the voltage level)
  // digitalWrite(LED_BUILTIN, HIGH);
  // // wait for a second
  // delay(1000);
  // // turn the LED off by making the voltage LOW
  // digitalWrite(LED_BUILTIN, LOW);
  //  // wait for a second
  // delay(1000);
  // for (int i = 0; i != 255; ++i){
  //   analogWrite(PA3, i);
  //   delay(10);
  // }
  // for (int i = 255; i != 0; --i){
  //   analogWrite(PA3, i);
  //   delay(10);
  // }
}
