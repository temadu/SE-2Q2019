#include "TP3.h"
#include <stdio.h> 
#include <math.h>
#include <Timer.h>
#include <Serial.h>
#include <PWM.h>

#define COMMAND_BUFFER_SIZE 16
#define SHORT_PRESS_CHECKS 5

volatile char commandBuffer[COMMAND_BUFFER_SIZE];

volatile signed int crankValue = 0;
volatile int izq = 0;

double getDecimal(double num){
 return ((num-(int)num)*10);
}

void sendStatus(){
  char buffer[50];
  double crankCalc = (crankValue*5.0)/1024.0;  
  sprintf(buffer, "crankADC: %d, crankVolt: %d.%d%d V\n", crankValue, (int) crankCalc, (int) getDecimal(crankCalc), (int) getDecimal(getDecimal(crankCalc)));
  sendStringSync(buffer);
  sprintf(buffer, "izq: %d\n", izq);
  sendStringSync(buffer);
  sendStringSync("\n");
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
  selectMuxChannel(2);
  startConversion();
  sei();
}


void motor(){

    setupTimer0();
    serialInit(9600);
    setupPWM();
    setupADC();
    
    PORTB |= 0x80;
    DDRB |= (1 << PORTB7); 

    PORTA |= 0b00000000;
    DDRA |= (1 << PORTA1) | (1 << PORTA2); 

    setInterval(100,sendStatus);
    
    while (1);
}


ISR(ADC_vect){
  crankValue = ADC;
  if(crankValue > 512){
    crankValue = (crankValue - 512);
    PORTA = 0b00000010;
    izq = 1;
  } else{
    crankValue = (512 - crankValue);
    PORTA = 0b00000100;
    izq = 2;
  }

  setPWMDutyCycle((crankValue/512.0) *100);
  startConversion();
}