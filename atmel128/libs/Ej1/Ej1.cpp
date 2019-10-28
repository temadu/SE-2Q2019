#include "Ej1.h"

volatile int delayCentiSecondsTimer = 0; 

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

ISR(TIMER0_COMP_vect){
  delayCentiSecondsTimer++;
}

void delay(int centiSecondsWait){
  int unlockTime = delayCentiSecondsTimer + centiSecondsWait;
  while(delayCentiSecondsTimer <= unlockTime){}
  delayCentiSecondsTimer = 0;
}