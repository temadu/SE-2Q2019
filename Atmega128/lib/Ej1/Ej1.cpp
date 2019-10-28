#include "Ej1.h"
#include <Timer.h>


void setupPWM(){
  TCCR2 |= (1 << COM21); // set non-inverting mode (On compare match, apaga el pin)
  TCCR2 |= (1 << WGM21) | (1 << WGM20); // set fast PWM Mode

  TIMSK |= (1 << TOIE2); // Enableeo el interrupt del clock

  TCCR2 |= (1 << CS20); // set prescaler to 1 and starts timer
}
void setPWMDutyCycle(int percent){
  if(percent > 100){
    OCR2 = 255;
  } else if (percent < 0) {
    OCR2 = 0;
  } else {
    OCR2 = (percent/100.0)*255.0;
  }
}

void ej1(){

    setupTimer0();
    // setupPWM();
    // setPWMDutyCycle(75);

    DDRB |= (1 << PORTB7); 
    PORTB = 0x00;

    while (1) {
        PORTB ^= 0x80;
        delay(50);
    }
}