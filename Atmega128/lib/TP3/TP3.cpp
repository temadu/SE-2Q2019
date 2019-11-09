#include "TP3.h"
#include<stdio.h> 
#include <Timer.h>
#include <Serial.h>
#include <PWM.h>

#define COMMAND_BUFFER_SIZE 16
#define SHORT_PRESS_CHECKS 5

volatile char commandBuffer[COMMAND_BUFFER_SIZE];

volatile int crankValue = 0;
volatile int thermValue = 0;

void sendStatus(){
  char buffer[25];
  sprintf(buffer, "crankADC: %d, thermistorADC: %d\n", crankValue, thermValue);
  sendStringSync(buffer);
}

void startConversion(){
  ADCSRA |= (1 << ADSC);
}

void selectMuxChannel(int chan){
  ADMUX = (ADMUX & 0xE0) | (chan & 0x1F);   //select channel (MUX0-4 bits)
}

void setupADC(){
  ADMUX |= (1 << REFS0); //USAR AVCC como ref (5volts)
  ADCSRA |= (1 << ADEN) | (1 << ADIE); //Start && interrupt mode
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); //Prescaler to 128
  selectMuxChannel(1);
  startConversion();
  sei();
}


void tp3(){

    setupTimer0();
    serialInit(9600);
    setupADC();
    DDRB |= (1 << PORTB7); 
    PORTB |= 0x80;

    setInterval(100,sendStatus);
    
    while (1);
}

volatile signed char isCrank = 0;
ISR(ADC_vect){
  if(isCrank){
    crankValue = ADC;
    selectMuxChannel(2);
  }else{
    selectMuxChannel(1);
    thermValue = ADC;
  }
  isCrank = !isCrank;
  startConversion();
}