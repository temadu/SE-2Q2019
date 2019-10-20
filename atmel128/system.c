// SYSTEM MODULE
// file: system.c
// Startup and system error recovery functions

#define F_CPU 14745600
#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

unsigned int tick = 0;
unsigned int seconds = 0;
#define TICKS_SECOND 14745600

#define LED_PIN 0xFF
void turnLedOff(){
	PORTB |= LED_PIN; //PORTB = PORTB | LED_PIN;
}

void turnLedOn(){
	PORTB &=~(LED_PIN);
}

int setupPWM(){
  OCR2 = 128; // set PWM for 50% duty cycle
  TCCR2 |= (1 << COM21); // set non-inverting mode (On compare match, apaga el pin)
  TCCR2 |= (1 << WGM21) | (1 << WGM20); // set fast PWM Mode

  TIMSK |= (1 << TOIE2); // Enableeo el interrupt del clock

  TCCR2 |= (1 << CS20); // set prescaler to 1 and starts timer

}

// funcion inicial
int main(void) {
  DDRB = 0xFF; // pone el puerto b como salida
  // PORTB = 0x00; //(1<<7);
  // PORTB = PORTB & ~(1<<7);


  // DDRB |= (1 << DDB3);
  // PB3 as output

  turnLedOn();
  while(1){
    turnLedOff();
    _delay_ms(500);
    turnLedOn();
    _delay_ms(500);
  }
  
}


