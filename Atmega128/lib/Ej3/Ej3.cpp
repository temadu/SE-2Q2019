#include "Ej1.h"

volatile int delayCentiSecondsTimer = 0; 
volatile int centiSecondsPassed = 0; 
volatile int centiSecondsToWait = 10; 

void setupTimer0(){
    TCCR0 |= (1 << WGM01); // CTC Mode
    OCR0 = 144;           // Cada cuantos Ticks quiero que levante el interrupt. https://eleccelerator.com/avr-timer-calculator/
    TIMSK |= (1 << OCIE0); // Enableeo el interrupt del clock

    sei();                // Seteo el flag de aceptar interrupts (es una instruccion de assembler que ni idea como hacer sin libreria)

    TCCR0 |= (1 << CS00) | (1 << CS01) | (1 << CS02); // 1024 Prescaler

}

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

volatile int buttonPushCounter = 0;   
volatile int buttonState = 0;  
volatile int lastButtonState = 0; 

void ej3(){
  DDRB |= (1 << PORTB7);  //B7 es unico output
  PORTB = 0x00;

  setupTimer0();
  // setupPWM();

  while (1){
    buttonState = (PINB & (1 << PORTB1));
    if (buttonState != lastButtonState) {
      if (buttonState) {
        buttonPushCounter++;
        if(buttonPushCounter > 3){
          buttonPushCounter = 0;
        }
      }
      delay(5);
    }
    lastButtonState = buttonState;
    if(buttonPushCounter == 0){
      centiSecondsToWait = 10;
    } else if (buttonPushCounter == 1){
      centiSecondsToWait = 50;
    } else {
      centiSecondsToWait = 100;
    }
  }
}

ISR(TIMER0_COMP_vect){
  delayCentiSecondsTimer++;
  centiSecondsPassed++;
  if(centiSecondsPassed > centiSecondsToWait){
    PORTB ^= (1 << PORTB7);
    centiSecondsPassed = 0;
  }
}

void delay(int centiSecondsWait){
  int unlockTime = delayCentiSecondsTimer + centiSecondsWait;
  while(delayCentiSecondsTimer <= unlockTime){}
  delayCentiSecondsTimer = 0;
}