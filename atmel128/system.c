// SYSTEM MODULE
// file: system.c
// Startup and system error recovery functions

#define F_CPU 14745600
#define F1 800
#define F2 200
#define F3 50

#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>

void setupTimer0();
void setupPWM();
void setPWMDutyCycle(int percent);;
void ej4();

void setPWMMode(int mode);
int centiSecondsPassed = 0; 

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

void ej4(){

    // setPWMDutyCycle(75);

    DDRB |= (1 << PORTB7);

    setupTimer0();
    // setupPWM();

    while (1) {

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

int buttonPushCounter = 0;

ISR(TIMER0_COMP_vect){
  centiSecondsPassed++;
  // setPWMDutyCycle(centiSecondsPassed * 5);
  if(centiSecondsPassed > 100){
    PORTB ^= (1 << PORTB7);
    // buttonPushCounter++;
    // setPWMMode(buttonPushCounter % 3);
    centiSecondsPassed = 0;
  }
}


// funcion inicial
int main(void) {
  ej4();
}


