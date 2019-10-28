#include "Ej3.h"

volatile int centiSecondsPassed = 0; 
volatile int centiSecondsToWait = 10; 

volatile int changerCentiSeconds = 0; 

void setupTimer0(){
    TCCR0 |= (1 << WGM01); // CTC Mode
    OCR0 = 144;           // Cada cuantos Ticks quiero que levante el interrupt. https://eleccelerator.com/avr-timer-calculator/
    TIMSK |= (1 << OCIE0); // Enableeo el interrupt del clock

    sei();                // Seteo el flag de aceptar interrupts (es una instruccion de assembler que ni idea como hacer sin libreria)

    TCCR0 |= (1 << CS00) | (1 << CS01) | (1 << CS02); // 1024 Prescaler

}

volatile int buttonPushCounter = 0;   
volatile int buttonState = 0;  
volatile int lastButtonState = 0; 

void ej3(){
  DDRB |= (1 << PORTB7);  //B7 es unico output
  PORTB |= (1 << PORTB1);

  setupTimer0();

  while (1){
    // buttonState = (PINB & (1 << PORTB1));
    // if (buttonState != lastButtonState) {
    //   if (buttonState) {
    //     buttonPushCounter++;
    //     if(buttonPushCounter > 3){
    //       buttonPushCounter = 0;
    //     }
    //   }
    //   delay(5);
    // }
    // lastButtonState = buttonState;
    if(changerCentiSeconds >= 100){
      buttonPushCounter++;
      if(buttonPushCounter > 3){
        buttonPushCounter = 0;
      }
      changerCentiSeconds = 0;
    }
    if(buttonPushCounter == 0){
      centiSecondsToWait = 10;
    } else if (buttonPushCounter == 1){
      centiSecondsToWait = 50;
    } else {
      centiSecondsToWait = 100;
    }

  }
}

checkInput(){
  return PINB & (1 << PORTB1);
}

ISR(TIMER0_COMP_vect){
  centiSecondsPassed++;
  if (!checkInput()){
    changerCentiSeconds++;
  } else {
    // changerCentiSeconds = 0;
  }
  if(centiSecondsPassed > centiSecondsToWait){
    PORTB ^= (1 << PORTB7);
    centiSecondsPassed = 0;
  }
}
