#include "PWM.h"

volatile double dutyCycle = 0; 

void setupPWM(){

  OCR2 = 0;

  TCCR2 |= (1 << COM21); // set non-inverting mode (On compare match, apaga el pin)
  TCCR2 |= (1 << WGM21) | (1 << WGM20); // set fast PWM Mode

  TIMSK |= (1 << TOIE2); // Enableeo el interrupt del clock
  sei();
  TCCR2 |= (1 << CS21);
}

void setPWMDutyCycle(double percent){
  if(percent > 100){
    dutyCycle = 100.0;
  } else if (percent < 0) {
    dutyCycle = 0.0;
  } else {
    dutyCycle = percent;
  }
}

ISR(TIMER2_OVF_vect){
  OCR2 = (dutyCycle/100.0)*255.0;
}