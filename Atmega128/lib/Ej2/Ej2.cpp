#include "Ej1.h"


void setupPWM(){
  OCR2 = 255;
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

void setPWMMode(int mode){
  switch(mode){
    case 0:
      setPWMDutyCycle(10);
      break;
    case 1:
      setPWMDutyCycle(50);
      break;
    case 2:
      setPWMDutyCycle(80);
      break;
  }
}

// ISR(TIMER0_COMP_vect){
//   centiSecondsPassed++;
//   if(centiSecondsPassed > 20){
//     PORTB ^= 0x80;
//     centiSecondsPassed = 0;
//   }
// }

// ISR(TIMER0_OVF_vect){
//   centiSecondsPassed++;
//   if(centiSecondsPassed > 20){
//     PORTB ^= 0x80;
//     centiSecondsPassed = 0;
//   }
// }

int buttonPushCounter = 0;   
int buttonState = 0;  
int lastButtonState = 0; 

void ej2(){
  DDRB |= (1 << PORTB7);  //B7 es unico output
  setupPWM();

  while (1){
    if (buttonState != lastButtonState) {
      if ((PINB & (1 << PORTB1))) {
        buttonPushCounter++;
      }
      //Delay para debounce 
    }
    lastButtonState = buttonState;

    setPWMMode(buttonPushCounter % 3);
  }
}