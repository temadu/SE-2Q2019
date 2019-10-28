#include "Timer.h"
#define CENTISECONDS_IN_YEAR 3153600000
#define MAX_INTERVALS_COUNT 25


volatile long delayCentiSecondsTimer = 0;

volatile long counters[MAX_INTERVALS_COUNT];
volatile void (*callbacks[MAX_INTERVALS_COUNT]) ();
volatile int lastFunction = 0;


void setupTimer0(){
    TCCR0 |= (1 << WGM01); // CTC Mode
    OCR0 = 144;           // Cada cuantos Ticks quiero que levante el interrupt. https://eleccelerator.com/avr-timer-calculator/
    TIMSK |= (1 << OCIE0); // Enableeo el interrupt del clock

    // sei();
    SREG|=0x80;

    TCCR0 |= (1 << CS00) | (1 << CS01) | (1 << CS02); // 1024 Prescaler

}


ISR(TIMER0_COMP_vect){
  delayCentiSecondsTimer++;
  if(delayCentiSecondsTimer >= CENTISECONDS_IN_YEAR){
    delayCentiSecondsTimer = 0;
  }
  for(int i = 0; i <= lastFunction; i++){
    if(counters[i] != 0 && (delayCentiSecondsTimer % counters[i]) == 0){
      (*callbacks[i]) ();
    }
  }
}

long getCentiseconds(){
  return delayCentiSecondsTimer;
}

int setInterval(long centiSeconds, void (*callback)(void)){
  lastFunction++;
  counters[lastFunction] = centiSeconds;
  callbacks[lastFunction] = callback;
  return lastFunction;
}

void clearInterval(int id){
  counters[lastFunction] = 0;
}


void delay(int centiSecondsWait){
  int unlockTime = delayCentiSecondsTimer + centiSecondsWait;
  while(delayCentiSecondsTimer <= unlockTime){}
  delayCentiSecondsTimer = 0;
}